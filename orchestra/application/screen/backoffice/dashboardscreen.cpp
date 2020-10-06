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
#include "dashboardscreen.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <screencommon.hpp>
#include <domain/dashboard/interface/dashboardiface.hpp>

namespace screen {
namespace backoffice {

Dashboard::Dashboard(const std::string& userID) : mUserID(userID) {
    // empty for now
}

void Dashboard::show(std::promise<screen::display>* promise) {
    SCREENCOMMON().showTopBanner();
    // Todo, provide dataiface and viewiface arguments
    using domain::dashboard::DashboardControlInterface;
    std::unique_ptr<DashboardControlInterface> coreDashboard
                    = domain::dashboard::createDashboardModule();
    coreDashboard->setCurrentUserId(mUserID);
    coreDashboard->PrintUser();
    // Todo, show user's full name here
    promise->set_value(screen::display::EXIT);
}

void Dashboard::showUserNotFound() {
    std::cout << "Current user was not found." << std::endl;
}

void Dashboard::showInvalidOptionPopup() {
    std::cout << "Sorry, that option is not yet available." << std::endl;
}

void Dashboard::showDataNotReadyScreen() {
    std::cout << "Data is not ready." << std::endl;
}

}  // namespace backoffice
}  // namespace screen
