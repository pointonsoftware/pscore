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
#include <utility>  // std utility
#include <logger/loghelper.hpp>
#include <general.hpp>  // pscore utility

namespace domain {
namespace authentication {

AuthController::AuthController(std::unique_ptr<AuthViewIface>&& view,
                               std::unique_ptr<AuthDataProviderIface>&& dataprovider)
: mView(std::move(view)), mDataProvider(std::move(dataprovider)) {
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
    if (!isPinValid(pin)) {
        mView->showInvalidPINScreen();
        return false;
    }

    // Get user info
    entity::User userInfo = getUserWithPIN(pin);

    // Validate
    if (!isUserValid(userInfo)) {
        LOG_INFO("User with PIN %s was not found", pin.c_str());
        mView->showUserNotFoundScreen();
        return false;
    }

    mView->loginSuccessful(userInfo);
    return true;
}

entity::User AuthController::getUserWithPIN(const std::string& pin) {
    // todo (xxx) : Check if dataprovider is ready; else throw
    if (!mDataProvider) {
        LOG_ERROR("Dataprovider is not initialized");
        return entity::User();
    }
    // Check pin in dataprovider
    return mDataProvider->findUserByPin(pin);
}

bool AuthController::isPinValid(const std::string& pin) {
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
bool AuthController::isUserValid(const entity::User& userInfo) {
    // If default pin is found, that means the user data was not initialized
    return userInfo.pin().find(entity::User::DEFAULT_PIN) == std::string::npos;
}


}  // namespace authentication
}  // namespace domain
