/**************************************************************************************************
*                                            PSCORE                                               *
*                               Copyright (C) 2020 Pointon Software                               *
*                                                                                                 *
*           This program is free software: you can redistribute it and/or modify                  *
*           it under the terms of the GNU Affero General Public License as published              *
*           by the Free Software Foundation, either version 3 of the License, or                  *
*           (at your option) any later version.                                                   *
*                                                                                                 *
*           This program is distributed in the hope that it will be useful,                       *
*           but WITHOUT ANY WARRANTY; without even the implied warranty of                        *
*           MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                         *
*           GNU Affero General Public License for more details.                                   *
*                                                                                                 *
*           You should have received a copy of the GNU Affero General Public License              *
*           along with this program.  If not, see <https://www.gnu.org/licenses/>.                *
*                                                                                                 *
*           Ben Ziv <pointonsoftware@gmail.com>                                                   *
*                                                                                                 *
**************************************************************************************************/
#include "authcontroller.hpp"
#include <general.hpp>  // pscore utility
#include <logger/loghelper.hpp>

namespace domain {
namespace authentication {

AuthController::AuthController(const std::shared_ptr<AuthDataProviderIface>& dataprovider,
                               const std::shared_ptr<AuthViewIface>& view)
: mView(view), mDataProvider(dataprovider) {
    // Empty for now
}

// cppcheck-suppress unusedFunction  ! remove this line when function is used
bool AuthController::login(const std::string& username, const std::string& password) {
    return true;
}

bool AuthController::loginWithPIN(const std::string& pin) {
    // Make sure view is valid
    if (!mView) {
        LOG_ERROR("View is not initialized");
        return false;
    }

    // Validate the PIN
    if (!isPinValid(pin)) {
        mView->showInvalidPINScreen();
        return false;
    }

    // Get user info
    entity::User userInfo;
    if (getUserByPIN(pin, &userInfo) != status::General::SUCCESS) {
        mView->showDataNotReadyScreen();
        return false;
    }

    // Validate user info
    if (!isUserValid(userInfo)) {
        LOG_INFO("User with PIN %s was not found", pin.c_str());
        mView->showUserNotFoundScreen();
        return false;
    }

    mView->loginSuccessful(userInfo);
    return true;
}

status::General AuthController::getUserByPIN(const std::string& pin, entity::User* user) {
    if (!user) {
        LOG_ERROR("Invalid user argument");
        return status::General::FAILED;
    }
    if (!mDataProvider) {
        LOG_ERROR("Dataprovider is not initialized");
        return status::General::UNINITIALIZED;
    }
    // todo (xxx) : Check if dataprovider is ready; else throw
    // Check pin in dataprovider
    *user = mDataProvider->findUserByPin(pin);

    return status::General::SUCCESS;
}

bool AuthController::isPinValid(const std::string& pin) const {
    if (pin.empty()) {
        LOG_WARN("PIN is empty");
        return false;
    }

    // Check if its numeric and valid size
    if (!utility::isNumber(pin) || pin.size() != entity::User::PIN_SIZE) {
        LOG_WARN("Invalid PIN: %s", pin.c_str());
        return false;
    }

    return true;
}
bool AuthController::isUserValid(const entity::User& userInfo) const {
    // Todo, this function should be moved to authdata
    // If default pin is found, that means the user data was not initialized
    return userInfo.pin().find(entity::User::DEFAULT_PIN) == std::string::npos;
}


}  // namespace authentication
}  // namespace domain
