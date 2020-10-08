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
// view
#include <screencommon.hpp>
// core
#include <domain/dashboard/interface/dashboardiface.hpp>
// data
#include <dashboarddata.hpp>
#include <entity/user.hpp>

namespace screen {
namespace backoffice {

DashboardScreen::DashboardScreen(const std::string& userID) : mUserID(userID) {
    // empty for now
}

void DashboardScreen::show(std::promise<screen::display>* promise) {
    using domain::dashboard::DashboardControlInterface;
    std::unique_ptr<DashboardControlInterface> coreDashboard
        = domain::dashboard::createDashboardModule(
                std::make_shared<dataprovider::dashboard::DashboardDataProvider>(),
                std::make_shared<DashboardScreen>(*this));
    coreDashboard->setCurrentUserId(mUserID);
    entity::User user = coreDashboard->getCurrentUserInfo();

    //--- Main Display

    SCREENCOMMON().showTopBanner();
    std::cout << "Hi " << user.getFullName() << ", what do you want to do today?" << std::endl;
    showOptions();

    Options userSelection;
    do {
        // Getting user input
        userSelection = getUserSelection();
        processOption(userSelection);
    } while (userSelection != Options::LOGOUT && userSelection != Options::APP_EXIT);

    //---

    // Setting the next screen
    promise->set_value(userSelection == Options::LOGOUT ? display::LOGIN : display::EXIT);
}

void DashboardScreen::showOptions() {
    std::cout << "[1] Personal Information" << std::endl;
    std::cout << "[0] Logout" << std::endl;
}

DashboardScreen::Options DashboardScreen::getUserSelection() {
    std::string userInput;
    std::cin >> userInput;

    // Todo (code), there might be a better/more effecient way to parse the user input
    if (userInput.find("x") != std::string::npos) {
        return Options::APP_EXIT;
    } else if (userInput.find("0") != std::string::npos) {
        return Options::LOGOUT;
    }  // add more options here

    // Return exit by default
    return Options::APP_EXIT;
}

void DashboardScreen::processOption(Options option) {
    switch (option) {
        case Options::LOGOUT:    // Fall-through
        case Options::APP_EXIT:  // Fall-through
        default:
            // Do nothing
            break;
    }
}

void DashboardScreen::showUserNotFound() {
    std::cout << "Current user was not found." << std::endl;
}

void DashboardScreen::showInvalidOptionPopup() {
    std::cout << "Sorry, that option is not yet available." << std::endl;
}

void DashboardScreen::showDataNotReadyScreen() {
    std::cout << "Data is not ready." << std::endl;
}

}  // namespace backoffice
}  // namespace screen
