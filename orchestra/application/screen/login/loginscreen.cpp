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
// view
#include <screencommon.hpp>
// core
#include <domain/userlogin/interface/loginiface.hpp>
// data
#include <logindata.hpp>

namespace screen {
namespace login {

void LoginScreen::show(std::promise<screen::display>* promise) {
    do {
        std::string pin;
        std::cout << "Input your PIN: ";
        std::cin >> pin;

        if (pin.find("x") != std::string::npos) {
            // exit was pressed
            promise->set_value(screen::display::EXIT);
            break;
        }
        if (onLogin(pin)) {
            // If login is successful, we show the dashboard
            promise->set_value(screen::display::DASHBOARD);
            break;
        }
    } while (1);
}

bool LoginScreen::onLogin(const std::string& pin) {
    std::unique_ptr<domain::login::LoginControlInterface> auth
         = domain::login::createLoginModule(
                    std::make_shared<dataprovider::login::LoginDataProvider>(),
                    std::make_shared<LoginScreen>(*this));

    mUserID = auth->loginWithPIN(pin);
    // If userID is empty, then the login attempt had failed
    // The failure reason should be shown in the screen/logs
    return mUserID.empty() ? false : true;
}

std::string LoginScreen::getUserID() const {
    return mUserID;
}

void LoginScreen::showInvalidPINScreen() {
    std::cout << "PIN is invalid, please try again." << std::endl;
}

void LoginScreen::showUserNotFoundScreen() {
    std::cout << "User PIN not found." << std::endl;
}

void LoginScreen::showDataNotReadyScreen() {
    std::cout << "Database not ready." << std::endl;
}

}  // namespace login
}  // namespace screen
