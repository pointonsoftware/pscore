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
#include <assert.h>
#include <memory>
#include <generalutils.hpp>  // pscore utility
#include <logger/loghelper.hpp>
#include <validator/uservalidator.hpp>

namespace domain {
namespace login {

LoginController::LoginController(const LoginDataPtr& dataprovider,
                                 const LoginViewPtr& view) : BaseController(dataprovider, view) {}

bool LoginController::authenticate(const std::string& id, const std::string& pin) {
    LOG_INFO("Authenticating");
    if (id.empty()) {
        LOG_WARN("ID is empty");
        mView->showUserNotFoundScreen();
        return false;
    }
    // Validate the PIN
    if (!isPinValid(pin)) {
        mView->showUserNotFoundScreen();
        return false;
    }
    // Get user info
    entity::User userInfo;
    if (getUser(utility::toUpper(id), &userInfo) != AUTHSTATUS::SUCCESS) {
        mView->showDataNotReadyScreen();
        return false;
    }
    // Validate user info
    if (!isUserValid(userInfo)) {
        LOG_WARN("User with ID %s was not found", id.c_str());
        mView->showUserNotFoundScreen();
        return false;
    }
    if (userInfo.pin() != pin) {
        LOG_WARN("User ID and PIN did not match");
        mView->showUserNotFoundScreen();
        return false;
    }

    LOG_INFO("User information found");
    return true;
}

AUTHSTATUS LoginController::getUser(const std::string& id, entity::User* user) {
    // The user argument must not be null
    assert(user != nullptr);
    // todo (xxx) : Check if dataprovider is ready; else throw
    LOG_DEBUG("Retrieving user data");
    // Check userID in dataprovider
    *user = mDataProvider->findUserByID(id);

    return AUTHSTATUS::SUCCESS;
}

bool LoginController::isPinValid(const std::string& pin) const {
    if (pin.empty()) {
        LOG_WARN("PIN is empty");
        return false;
    }
    {
        // Data for PIN validation only
        entity::User userInfo("Proxy", "Proxy", pin, "2020-10-10 10:10:10", "Proxy");
        entity::validator::UserValidator validator(userInfo);
        // Check if its numeric and valid size
        if (!validator.result().empty()) {
            LOG_WARN("Invalid PIN");
            return false;
        }
    }
    LOG_DEBUG("Received a valid PIN");
    return true;
}

bool LoginController::isUserValid(const entity::User& userInfo) const {
    LOG_DEBUG("Validating user data");
    // If userID is empty, that means the user data was not initialized
    return !userInfo.userID().empty();
}

LoginControllerPtr createLoginModule(const LoginDataPtr& dataprovider,
                                     const LoginViewPtr& view) {
    return std::make_unique<LoginController>(dataprovider, view);
}

}  // namespace login
}  // namespace domain
