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
#include <backoffice/dashboard.hpp>
// core
#include <domain/userlogin/logincontroller.hpp>
// data
#include <logindata.hpp>

namespace view {
namespace login {

void LoginScreen::show() {
    do {
        std::string pin;
        std::cout << "Input your PIN: ";
        std::cin >> pin;

        if(pin.find("x") != std::string::npos) {
            break;
        }
        if(onLogin(pin)) {
            PIN = pin;
            break;
        }
    } while (1);
    // Todo: return the inputed PIN to flow controller
}

bool LoginScreen::onLogin(const std::string& pin) {
    domain::login::LoginController auth(
                    std::make_shared<dataprovider::login::LoginDataProvider>(),
                    std::make_shared<login::LoginScreen>(*this));
    return auth.loginWithPIN(pin);
}

std::string LoginScreen::getPinEntered() const {
    return PIN;
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
}  // namespace view
