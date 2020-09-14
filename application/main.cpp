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
#include <domain/controller/authcontroller.hpp>
#include <logger/loghelper.hpp>

int main() {
    domain::authentication::AuthController auth(nullptr, nullptr);
    std::string name;

    std::cout << "Hi there, Welcome to Core! What's your name?" << std::endl;
    std::cin >> name;

    LOG_DEBUG("Hello %s, I'm using the core logger to print this debug message!", name.c_str());
    return 0;
}