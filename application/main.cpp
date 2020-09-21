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

/* NOTE!
 * When updating the std::cin's of console_app, update ci/automation_input.txt as well.
*/

#include <iostream>
#include <cstdlib>
#include <domain/userlogin/authcontroller.hpp>
#include <logger/loghelper.hpp>

void showWelcomeScreen() {
    std::cout << "******************************************************************" << std::endl;
    std::cout << "*\t\t\t\t\t\t\t\t *" << std::endl;
    std::cout << "*\t\t\t\t PSCORE \t\t\t *" << std::endl;
    std::cout << "*\t\t\t    Pointon Software  \t\t\t *" << std::endl;
    std::cout << "*\t\t\t\t\t\t\t\t *" << std::endl;
    std::cout << "******************************************************************" << std::endl;
    std::cout << "Hi there, Welcome to Core!" << std::endl;
}

void clearScreen() {
#ifdef __WIN32__
    std::system("cls");
#else
    std::system("clear");
#endif
}

void showUserInfoScreen() {
    std::cout << "******************************************************************" << std::endl;
    std::cout << "*\t\t\t\t\t\t\t\t *" << std::endl;
    std::cout << "*\t\t\t\t PSCORE \t\t\t *" << std::endl;
    std::cout << "*\t\t\t    Pointon Software  \t\t\t *" << std::endl;
    std::cout << "*\t\t\t\t\t\t\t\t *" << std::endl;
    std::cout << "******************************************************************" << std::endl;
    std::cout << "Hi dummy, what do you want to do today?" << std::endl;
}

int main() {
    showWelcomeScreen();

    domain::authentication::AuthController auth(nullptr, nullptr);
    std::string pin;
    std::cout << "Input your PIN: ";

    std::cin >> pin;

    if (auth.loginWithPIN(pin)) {
        clearScreen();
        showUserInfoScreen();
    } else {
        std::cout << "Sorry, I can't find your info." << std::endl;
    }


    return 0;
}