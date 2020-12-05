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
#include "logincontroller.hpp"
#include <memory>
#include <general.hpp>  // pscore utility
#include <logger/loghelper.hpp>
#include <validator/uservalidator.hpp>

namespace domain {
namespace login {

LoginController::LoginController(const std::shared_ptr<LoginDataProviderIface>& dataprovider,
                               const std::shared_ptr<LoginViewIface>& view)
: mDataProvider(dataprovider), mView(view) {
    // Empty for now
}

bool LoginController::authenticate(const std::string& id, const std::string& pin) {
    // Make sure view is valid
    if (!mView) {
        LOG_ERROR("View is not initialized");
        return false;
    }
    if (id.empty()) {
        LOG_WARN("ID is empty");
        return false;
    }
    // Validate the PIN
    if (!isPinValid(pin)) {
        mView->showInvalidPINScreen();
        return false;
    }
    // Get user info
    entity::User userInfo;
    if (getUserByPIN(pin, &userInfo) != AUTHSTATUS::SUCCESS) {
        mView->showDataNotReadyScreen();
        return false;
    }
    // Validate user info
    if (!isUserValid(userInfo)) {
        LOG_WARN("User with PIN %s was not found", pin.c_str());
        mView->showUserNotFoundScreen();
        return false;
    }

    LOG_INFO("User with PIN %s was found", pin.c_str());
    return true;
}

AUTHSTATUS LoginController::getUserByPIN(const std::string& pin, entity::User* user) {
    if (!user) {
        LOG_ERROR("Invalid user argument");
        return AUTHSTATUS::FAILED;
    }
    if (!mDataProvider) {
        LOG_ERROR("Dataprovider is not initialized");
        return AUTHSTATUS::UNINITIALIZED;
    }

    // todo (xxx) : Check if dataprovider is ready; else throw
    LOG_DEBUG("Retrieving user data");
    // Check pin in dataprovider
    *user = mDataProvider->findUserByPin(pin);

    return AUTHSTATUS::SUCCESS;
}

bool LoginController::isPinValid(const std::string& pin) const {
    if (pin.empty()) {
        LOG_WARN("PIN is empty");
        return false;
    }
    {
        entity::User userInfo("Proxy", "Proxy", pin, "Proxy");
        entity::validator::UserValidator validator(userInfo);
        // Check if its numeric and valid size
        if (!validator.result().empty()) {
            LOG_WARN("Invalid PIN: %s", pin.c_str());
            return false;
        }
    }
    LOG_DEBUG("PIN is valid");
    return true;
}

bool LoginController::isUserValid(const entity::User& userInfo) const {
    LOG_DEBUG("Validating user data");
    // If userID is empty, that means the user data was not initialized
    return !userInfo.userID().empty();
}

std::unique_ptr<LoginControlInterface> createLoginModule(
    const std::shared_ptr<LoginDataProviderIface>& dataprovider,
    const std::shared_ptr<LoginViewIface>& view) {
    return std::make_unique<LoginController>(dataprovider, view);
}

}  // namespace login
}  // namespace domain
