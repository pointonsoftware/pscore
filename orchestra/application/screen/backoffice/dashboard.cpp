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
#include "dashboard.hpp"
#include <iostream>
#include <string>
#include <screencommon.hpp>

namespace screen {
namespace backoffice {

Dashboard::Dashboard(const std::string& userID) : mUserID(userID) {
    // empty for now
}

void Dashboard::show(std::promise<screen::display>* promise) {
    SCREENCOMMON().showTopBanner();
    // Todo, retrieve the userinfo from db using userID
    // dashboardDataProvider->getUserInfo(mUserID);

    // Todo, show user's full name here
    std::cout << "Hi " << mUserID << ", what do you want to do today?" << std::endl;

    promise->set_value(screen::display::EXIT);

}

}  // namespace backoffice
}  // namespace screen