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
// view
#include <informationscreen.hpp>
#include <screencommon.hpp>

// data
#include <dashboarddata.hpp>

namespace screen {
namespace backoffice {

DashboardScreen::DashboardScreen(const std::string& userID) : mUserID(userID) {
    // empty for now
}

void DashboardScreen::show(std::promise<defines::display>* promise) {
    mCoreController = domain::dashboard::createDashboardModule(
                std::make_shared<dataprovider::dashboard::DashboardDataProvider>(),
                std::make_shared<DashboardScreen>(mUserID));
    mCoreController->setCurrentUserId(mUserID);
    mCurrentUser = mCoreController->getCurrentUser();

    if (!mCurrentUser.userID().empty()) {
        // Valid user, proceed to menu selection
        menuSelection(promise);
    } else {
        // Current user was not found or has insufficient data
        promise->set_value(defines::display::LOGIN);
        // Wait for user confirmation before switching screen
        std::cin.ignore(); std::cin.get();
    }
}

void DashboardScreen::menuSelection(std::promise<defines::display>* promise) const {
    showLandingScreen();
    // Stay in dashboard until action() returns false (i.e. switch screen is required)
    do {} while (action(getUserSelection(), promise));
}

void DashboardScreen::showLandingScreen() const {
    SCREENCOMMON().showTopBanner("Dashboard");
    std::cout << "Hi " << mCurrentUser.userID()
              << ", please select an option below." << std::endl;
    showOptions();
}

void DashboardScreen::showOptions() const {
    std::cout << std::endl;
    std::cout << "[1] Personal Information" << std::endl;
    std::cout << "[2] Employee Management" << std::endl;
    std::cout << "[3] Inventory Control" << std::endl;
    std::cout << "[4] Customer Management" << std::endl;
    std::cout << "[0] Logout" << std::endl;
}

void DashboardScreen::showUserInformation() const {
    SCREENCOMMON().showTopBanner("User Information");
    if (!mCurrentUser.employeeID().empty()) {
        entity::Employee emp = mCoreController->getUserDetails(mCurrentUser);
        screen::InformationScreen<entity::Employee> userInfoScreen(emp);
        userInfoScreen.showBasicInformation();
        userInfoScreen.showContactDetails();
        userInfoScreen.showAddress();
        userInfoScreen.showPersonalIds();
        // Show user data
        {
            screen::InformationScreen<entity::User> userDataScreen(mCurrentUser);
            userDataScreen.showBasicInformation();
        }
    } else {
        std::cout << "No data." << std::endl;
    }
    std::cout << std::endl << std::endl;
    std::cout << "Enter [b] to go back." << std::endl;
}

void DashboardScreen::invalidOptionSelected() const {
    std::cout << "Invalid option! Please select a choice from the menu." << std::endl;
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
        return Options::USER_PROFILE;
    } else if (userInput == "2") {
        return Options::EMPLOYEE_MGMT;
    } else if (userInput == "3") {
        return Options::INVENTORY_CTRL;
    } else if (userInput == "4") {
        return Options::CUSTOMER_MGMT;
    }  // add more options here

    // Default invalid option
    return Options::INVALID;
}

bool DashboardScreen::action(Options option, std::promise<defines::display>* nextScreen) const {
    bool switchScreenIsRequired = false;
    switch (option) {
        case Options::LANDING:
            showLandingScreen();
            break;
        case Options::USER_PROFILE:
            showUserInformation();
            break;
        case Options::INVALID:
            invalidOptionSelected();
            break;
        case Options::EMPLOYEE_MGMT:
            switchScreenIsRequired = true;
            nextScreen->set_value(defines::display::EMPMGMT);
            break;
        case Options::INVENTORY_CTRL:
            switchScreenIsRequired = true;
            nextScreen->set_value(defines::display::INVENTORY);
            break;
        case Options::CUSTOMER_MGMT:
            switchScreenIsRequired = true;
            nextScreen->set_value(defines::display::CUSTMGMT);
            break;
        case Options::LOGOUT:
            switchScreenIsRequired = true;
            nextScreen->set_value(defines::display::LOGIN);
            break;
        case Options::APP_EXIT:  // Fall-through
        default:
            switchScreenIsRequired = true;
            nextScreen->set_value(defines::display::EXIT);
            break;
    }
    // Return "false" if switch screen is required so we can exit dashboard
    return !switchScreenIsRequired;
}

void DashboardScreen::showUserNotFound() {
    std::cout << "Current user was not found." << std::endl;
}

void DashboardScreen::showInvalidOptionPopup() {
    std::cout << "Sorry, that option is not available." << std::endl;
}

void DashboardScreen::showDataNotReadyScreen() {
    std::cout << "Data is not ready." << std::endl;
}

}  // namespace backoffice
}  // namespace screen
