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
#include "empmgmtscreen.hpp"
#include <iostream>
#include <memory>
#include <string>
// view
#include <screencommon.hpp>
// core
#include <domain/employeemgmt/interface/employeemgmtiface.hpp>

namespace screen {
namespace backoffice {

void EmployeeMgmtScreen::show(std::promise<defines::display>* promise) {
    showLandingScreen();
    /*! Screen navigation
     * Stay in the current screen until action() returns false (i.e. switch screen is required)
    */
    do {} while (action(getUserSelection(), promise));
}

void EmployeeMgmtScreen::showLandingScreen() const {
    SCREENCOMMON().showTopBanner("Employee Management");
    showUsersList();
    showOptions();
}

void EmployeeMgmtScreen::showUsersList() const {
    std::cout << std::endl;
    // Todo (code) - PCOR-34
    // Display the columns
    // Get the vector of employees, iterate (increment [N] option)
    std::cout << "[1] Id123 -- Dummy Dummy -- Foo Bar" << std::endl;
    std::cout << "[2] Id456 -- Dummy Dummy -- Foo Bar" << std::endl;
}

void EmployeeMgmtScreen::showOptions() const {
    std::cout << std::endl;
    std::cout << "[b] Back" << std::endl;
    std::cout << "[0] Logout" << std::endl;
    std::cout << std::endl;
    std::cout << "Select by entering [option]" << std::endl;
}

EmployeeMgmtScreen::Options EmployeeMgmtScreen::getUserSelection() const {
    std::string userInput;
    std::cout << std::endl << "> "; std::cin >> userInput;

    if (userInput == "x") {
        return Options::APP_EXIT;
    } else if (userInput == "b") {
        // Todo (code) - we should return whatever was the previous screen
        // return Options::LANDING;
        return Options::DASHBOARD;
    } else if (userInput == "0") {
        return Options::LOGOUT;
    }  // add more options here

    // Default invalid option
    return Options::INVALID;
}

bool EmployeeMgmtScreen::action(Options option, std::promise<defines::display>* nextScreen) const {
    bool switchScreenIsRequired = false;
    switch (option) {
        case Options::LANDING:
            showLandingScreen();
            break;
        case Options::INVALID:
            invalidOptionSelected();
            break;
        case Options::DASHBOARD:
            switchScreenIsRequired = true;
            nextScreen->set_value(defines::display::DASHBOARD);
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
    // Return "false" if switch screen is required so we proceed to the next screen
    return !switchScreenIsRequired;
}

void EmployeeMgmtScreen::invalidOptionSelected() const {
    std::cout << "Sorry, that option is not yet available." << std::endl;
}

void EmployeeMgmtScreen::showEmployeeInformation() const {
    // Todo (code) - create an employee info screen, pass the info as parameter
    //             - it has to decide on wether user or employee will be displayed
    //             - pass a parameter of wether to display the CUD options
    // Todo (code) - we will switch to the user/employee info screen
}

void EmployeeMgmtScreen::showEmployeesEmptyPopup() {
    std::cout << "Employees record is empty." << std::endl;
}

void EmployeeMgmtScreen::showDataNotReadyScreen() {
    std::cout << "Data is not ready." << std::endl;
}

}  // namespace backoffice
}  // namespace screen
