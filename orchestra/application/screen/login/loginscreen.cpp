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
#include "loginscreen.hpp"
#include <iostream>
#include <memory>
#include <string>
// view
#include <screencommon.hpp>
// data
#include <logindata.hpp>
#include <logger/loghelper.hpp>

namespace screen {
namespace login {

void LoginScreen::show(std::promise<defines::display>* promise) {
    // Welcome to Core!
    SCREENCOMMON().showTopBanner("Login");
    std::cout << "Hi there, Welcome to Core!" << std::endl;

    do {
        std::string id;
        std::string pin;
        LOG_DEBUG("Waiting for user login details");
        if (((id = SCREENCOMMON().getInput("ID")) == "x") ||
            ((pin = SCREENCOMMON().getInput("Pin")) == "x")) {
            // exit was pressed
            promise->set_value(defines::display::EXIT);
            break;
        }
        if (onLogin(id, pin)) {
            // If login is successful, set userID then show the dashboard
            mUserID = id;
            promise->set_value(defines::display::DASHBOARD);
            break;
        }
    } while (1);
}

bool LoginScreen::onLogin(const std::string& id, const std::string& pin) {
    domain::login::LoginControllerPtr coreController = domain::login::createLoginModule(
                            std::make_shared<dataprovider::login::LoginDataProvider>(),
                            std::make_shared<LoginScreen>());
    return coreController->authenticate(id, pin);
}

std::string LoginScreen::getUserID() const {
    return mUserID;
}

void LoginScreen::showUserNotFoundScreen() {
    std::cout << "User not found." << std::endl;
}

void LoginScreen::showDataNotReadyScreen() {
    std::cout << "Database not ready." << std::endl;
}

}  // namespace login
}  // namespace screen
