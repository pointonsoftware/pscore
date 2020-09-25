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
#include "authview.hpp"
#include <iostream>
#include <viewcommon.hpp>


namespace view {
namespace authentication {

void AuthView::loginSuccessful(const entity::User& userInfo) {
    SCREENCOMMON().clearScreen();
    SCREENCOMMON().showTopBanner();
    // Todo, display user name here
    std::cout << "Hi dummy, what do you want to do today?" << std::endl;
}
void AuthView::showInvalidPINScreen() {
    std::cout << "PIN is invalid, please try again." << std::endl;
}

void AuthView::showUserNotFoundScreen() {
    std::cout << "User PIN not found." << std::endl;
}

void AuthView::showDataNotReadyScreen() {
    std::cout << "Database not ready." << std::endl;
}

}  // namespace authentication
}  // namespace view