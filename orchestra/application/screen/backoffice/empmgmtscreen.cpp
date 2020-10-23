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
#include <string>
#include <vector>
#include <general.hpp>  // pscore utility
// view
#include <informationscreen.hpp>
#include <screencommon.hpp>
// data
#include <employeedata.hpp>

namespace screen {
namespace backoffice {

void EmployeeMgmtScreen::show(std::promise<defines::display>* promise) {
    // Get the employees from Core then cache the list
    queryEmployeesList();
    // Landing
    showLandingScreen();
    /*! Screen navigation
     * Stay in the current screen until action() returns false (i.e. switch screen is required)
    */
    do {} while (action(getUserSelection(), promise));
}

void EmployeeMgmtScreen::showLandingScreen() const {
    SCREENCOMMON().showTopBanner("Employee Management");
    showEmployees();
    showOptions();
}

void EmployeeMgmtScreen::queryEmployeesList() {
    using domain::empmgmt::EmployeeMgmtControlInterface;
    std::unique_ptr<EmployeeMgmtControlInterface> coreEmployeeMgmt
        = domain::empmgmt::createEmployeeMgmtModule(
                std::make_shared<dataprovider::empmgmt::EmployeeDataProvider>(),
                std::make_shared<EmployeeMgmtScreen>(*this));
    mEmployees = coreEmployeeMgmt->list();
}

void EmployeeMgmtScreen::showEmployees() const {
    std::cout << std::endl;
    // Display the columns
    SCREENCOMMON().printColumns({"Employee ID", "First Name", "Last Name", "Position"}, true);
    // Display employees
    for (unsigned int index = 0; index < mEmployees.size(); ++index) {
        SCREENCOMMON().printColumns({
            std::string("[" + std::to_string(index + 1) + "] " + mEmployees[index].employeeID()),
            mEmployees[index].firstName(),
            mEmployees[index].lastName(),
            mEmployees[index].position()
        });
    }
    SCREENCOMMON().printHorizontalBorder(defines::BORDER_CHARACTER_2);
}

void EmployeeMgmtScreen::showOptions() const {
    std::cout << std::endl;
    std::cout << "[b] Back" << std::endl;
    std::cout << "[0] Logout" << std::endl;
    std::cout << std::endl;
}

EmployeeMgmtScreen::Options EmployeeMgmtScreen::getUserSelection() {
    std::string userInput;
    std::cout << std::endl << "Select [option] > "; std::cin >> userInput;

    if (userInput == "x") {
        return Options::APP_EXIT;
    } else if (userInput == "b") {
        // Todo (code) - we should return whatever was the previous screen
        // For now, we will check if user has selected an index (i.e. info screen is shown)
        if (mSelectedEmployeeIndex == 0) {
            return Options::DASHBOARD;
        }
        mSelectedEmployeeIndex = 0;  // reset whenever we go to landing
        return Options::LANDING;
    } else if (userInput == "0") {
        return Options::LOGOUT;
    } else if (utility::isNumber(userInput)) {
        mSelectedEmployeeIndex = std::stoi(userInput);
        return Options::EMPLOYEE_DETAILS;
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
        case Options::EMPLOYEE_DETAILS:
            mSelectedEmployeeIndex > (mEmployees.size()) ?
                invalidOptionSelected() : showEmployeeInformation();
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

    // mSelectedEmployeeIndex is a 1-based index but vector is zero-based (hence minus 1)
    entity::Employee selectedEmployee = mEmployees[mSelectedEmployeeIndex - 1];
    if (!selectedEmployee.employeeID().empty()) {
        // Valid employee, show the information screen!
        SCREENCOMMON().showTopBanner("Employee Information");
        screen::InformationScreen<entity::Employee> infoScreen(selectedEmployee);
        infoScreen.showBasicInformation();
        infoScreen.showContactDetails();
        infoScreen.showUserAddress();
        infoScreen.showUserPersonalIds();
        std::cout << std::endl << std::endl;
        std::cout << "Enter [b] to go back." << std::endl;
    }
}

void EmployeeMgmtScreen::showEmployeesEmptyPopup() {
    std::cout << "Employees record is empty." << std::endl;
}

void EmployeeMgmtScreen::showDataNotReadyScreen() {
    std::cout << "Data is not ready." << std::endl;
}

}  // namespace backoffice
}  // namespace screen
