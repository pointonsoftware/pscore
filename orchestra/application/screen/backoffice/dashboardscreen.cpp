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
    mCurrentUser = coreDashboard->getCurrentUserInfo();

    //--- Main Display

    showLandingScreen();

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

void DashboardScreen::showLandingScreen() const {
    SCREENCOMMON().showTopBanner("Dashboard");
    std::cout << "Hi " << mCurrentUser.getFullName()
              << ", please select an option below." << std::endl;
    showOptions();
}

void DashboardScreen::showOptions() const {
    std::cout << std::endl;
    std::cout << "[1] Personal Information" << std::endl;
    std::cout << "[0] Logout" << std::endl;
}

void DashboardScreen::showUserInformation() const {
    SCREENCOMMON().showTopBanner("User Information");
    // Todo (code), this needs to be updated to have a proper console screen layout
    std::cout << "First Name  : " << mCurrentUser.firstName() << std::endl;
    std::cout << "Middle Name : " << mCurrentUser.middleName() << std::endl;
    std::cout << "Last Name   : " << mCurrentUser.lastName() << std::endl;
    std::cout << "Birthdate   : " << mCurrentUser.birthdate() << std::endl;
    std::cout << "Gender      : " << mCurrentUser.gender() << std::endl;
    std::cout << "Email       : " << mCurrentUser.email() << std::endl;
    // Todo (code), add Contact details, address and personal ID
    std::cout << std::endl << std::endl;
    std::cout << "Enter [b] to go back." << std::endl;
}

void DashboardScreen::invalidOptionSelected() const {
    std::cout << "Invalid option! Please select a number from the menu." << std::endl;
}

DashboardScreen::Options DashboardScreen::getUserSelection() const {
    std::string userInput;
    std::cout << std::endl << "> "; std::cin >> userInput;

    if (userInput == "x") {
        return Options::APP_EXIT;
    } else if (userInput == "b") {
        return Options::LANDING;
    } else if (userInput == "0") {
        return Options::LOGOUT;
    } else if (userInput == "1") {
        return Options::USER_DETAILS;
    }  // add more options here

    // Default invalid option
    return Options::INVALID;
}

void DashboardScreen::processOption(Options option) const {
    switch (option) {
        case Options::LANDING:
            showLandingScreen();
            break;
        case Options::USER_DETAILS:
            showUserInformation();
            break;
        case Options::INVALID:
            invalidOptionSelected();
            break;
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
