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
#ifndef APPLICATION_SCREEN_BANNER_HPP_
#define APPLICATION_SCREEN_BANNER_HPP_
#include <iostream>

#define VERSION "0.0.1"

namespace screen {

std::string horizontalBorder() {
    return "*********************************************************************************";
}
void showTopBanner() {
    std::cout << horizontalBorder() << std::endl;
    std::cout << "*\t\t\t\t\t\t\t\t\t\t*" << std::endl;
    std::cout << "*\t\t\t\t---- CORE " << VERSION << " ----\t\t\t\t*" << std::endl;
    std::cout << "*\t\t\t\tConsole  Application\t\t\t\t*" << std::endl;
    std::cout << "*\t\t\t\t\t\t\t\t\t\t*" << std::endl;
    std::cout << horizontalBorder() << std::endl;
}

}  // namespace screen

#endif  // APPLICATION_SCREEN_BANNER_HPP_