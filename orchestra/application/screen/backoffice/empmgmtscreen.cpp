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
#include <functional>
#include <iostream>
#include <string>
#include <unordered_map>
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
    mCoreEmployeeMgmt = domain::empmgmt::createEmployeeMgmtModule(
                    std::make_shared<dataprovider::empmgmt::EmployeeDataProvider>(),
                    std::make_shared<EmployeeMgmtScreen>());
    // Get the employees from Core then cache the list
    queryEmployeesList();
    // Landing
    showLandingScreen();
    /*!
     * Screen navigation
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
    mEmployeesGUITable = mCoreEmployeeMgmt->list();
}

void EmployeeMgmtScreen::createEmployee() {
    std::cout << std::endl << "Add Employee - type [space] for empty entry" << std::endl;
    entity::Employee* newEmployee = new entity::User();

    // Todo (code) - move this to a specific function
    auto inputArea =
    [](std::function<void(const std::string&)> func,
        const std::string& label) {
        func(SCREENCOMMON().getInput(label));
    };

    inputArea(std::bind(&entity::Employee::setFirstName, newEmployee,
              std::placeholders::_1), "First Name");
    inputArea(std::bind(&entity::Employee::setMiddleName, newEmployee,
              std::placeholders::_1), "Middle Name");
    inputArea(std::bind(&entity::Employee::setLastName, newEmployee,
              std::placeholders::_1), "Last Name");
    inputArea(std::bind(&entity::Employee::setBirthdate, newEmployee,
              std::placeholders::_1), "Date of Birth (dd/mm/yyyy)");
    inputArea(std::bind(&entity::Employee::setGender, newEmployee,
              std::placeholders::_1), "Gender (M/F)");
    inputArea(std::bind(&entity::Employee::setPosition, newEmployee,
              std::placeholders::_1), "Position");
    // Address
    {
        entity::Address address;
        address.housenumber = SCREENCOMMON().getInput("House Number");
        address.lot         = SCREENCOMMON().getInput("Lot Number");
        address.block       = SCREENCOMMON().getInput("Block");
        address.street      = SCREENCOMMON().getInput("Street");
        address.subdivision = SCREENCOMMON().getInput("Subdivision");
        address.sitio       = SCREENCOMMON().getInput("Sitio");
        address.purok       = SCREENCOMMON().getInput("Purok");
        address.barangay    = SCREENCOMMON().getInput("Barangay");
        address.city_town   = SCREENCOMMON().getInput("City/Town");
        address.province    = SCREENCOMMON().getInput("Province");
        address.zip         = SCREENCOMMON().getInput("Zip");
        newEmployee->setAddress(address);
    }
    // Contact details
    {
        entity::ContactDetails contactDetails;
        contactDetails.phone_number_1 = SCREENCOMMON().getInput("Phone Number 1");
        contactDetails.phone_number_2 = SCREENCOMMON().getInput("Phone Number 2");
        contactDetails.email          = SCREENCOMMON().getInput("Email Address");
        newEmployee->setPhoneNumbers(contactDetails.phone_number_1, contactDetails.phone_number_2);
        newEmployee->setEmail(contactDetails.email);
    }
    // Ask if user wants to input a valid/government ID
    if (SCREENCOMMON().getYesNoInput("Has valid/government ID (y/n)") == "y") {
        entity::PersonalId personalId;
        personalId.type      = SCREENCOMMON().getInput("ID Type");
        personalId.id_number = SCREENCOMMON().getInput("ID Number");
        newEmployee->addPersonalId(personalId.type, personalId.id_number);
    }
    /*!
     * Todo (code)
     * - do findByName(fname, lname) first
     * - if found, show "An employee name Foo Bar with ID xxxx exists,
     *                   do you want to update this employee instead?"
    */
    if (SCREENCOMMON().getYesNoInput("System User (y/n)") == "n") {
        // non-user, add the employee
        std::unordered_map<std::string, std::string> validationResult;
        domain::empmgmt::USERSMGMTSTATUS status =
                 mCoreEmployeeMgmt->save(*newEmployee, &validationResult);
        if (status != domain::empmgmt::USERSMGMTSTATUS::SUCCESS) {
            for (auto const &result : validationResult) {
                std::cout << result.first << " -> " << result.second << std::endl;
            }
            // Let the user confirm after viewing the validation results
            std::cin.ignore();
            std::cin.get();
        } else {
            std::cout << "Employee " << newEmployee->getFullName()
                      << " added successfully!" << std::endl;
        }
    } else {
        // Employee is a system user
        entity::User* newUser = dynamic_cast<entity::User*>(newEmployee);
        // get PIN
        newUser->setPIN(SCREENCOMMON().getInput("PIN"));
        // Todo (code) - call core::createUser
        std::cout << "New user " << newUser->getFullName() <<
                     " PIN: " << newUser->pin() << std::endl;
    }
    delete newEmployee;
}

void EmployeeMgmtScreen::removeEmployee() {
    if (mCoreEmployeeMgmt->remove(mEmployeesGUITable[mSelectedEmployeeIndex - 1].employeeID())
          == domain::empmgmt::USERSMGMTSTATUS::SUCCESS) {
       // Remove the user form
       mEmployeesGUITable.erase(mEmployeesGUITable.begin() + (mSelectedEmployeeIndex - 1));
    }
}

void EmployeeMgmtScreen::showEmployees() const {
    std::cout << std::endl;
    // Display the columns
    SCREENCOMMON().printColumns({"Employee ID", "First Name", "Last Name", "Position"}, true);
    // Display employees
    for (unsigned int index = 0; index < mEmployeesGUITable.size(); ++index) {
        SCREENCOMMON().printColumns({
            std::string("[" + std::to_string(index + 1) + "] "
                         + mEmployeesGUITable[index].employeeID()),
            mEmployeesGUITable[index].firstName(),
            mEmployeesGUITable[index].lastName(),
            mEmployeesGUITable[index].position()
        });
    }
    SCREENCOMMON().printHorizontalBorder(defines::BORDER_CHARACTER_2);
}

void EmployeeMgmtScreen::showOptions() const {
    std::cout << std::endl << std::endl;
    SCREENCOMMON().printColumns({"[b] - Back", "[c] - Create", "[0] - Logout"},
                                 true, false);
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
        return Options::LANDING;
    } else if (userInput == "0") {
        return Options::LOGOUT;
    } else if (utility::isNumber(userInput)) {
        // Store user input as the selected index
        mSelectedEmployeeIndex = std::stoi(userInput);
        return Options::EMPLOYEE_DETAILS;
    } else if (userInput == "c") {
        return Options::EMPLOYEE_CREATE;
    } else if (userInput == "d") {
        return Options::EMPLOYEE_REMOVE;
    }  // add more options here

    // Default invalid option
    return Options::INVALID;
}

bool EmployeeMgmtScreen::action(Options option, std::promise<defines::display>* nextScreen) {
    bool switchScreenIsRequired = false;
    switch (option) {
        case Options::LANDING:
            mSelectedEmployeeIndex = 0;  // reset whenever we go to landing
            showLandingScreen();
            break;
        case Options::INVALID:
            invalidOptionSelected();
            break;
        case Options::EMPLOYEE_DETAILS:
            mSelectedEmployeeIndex > (mEmployeesGUITable.size()) ?
                invalidOptionSelected() : showEmployeeInformation();
            break;
        case Options::EMPLOYEE_CREATE:
            createEmployee();
            // Get the employees from Core then cache the list
            queryEmployeesList();
            showLandingScreen();
            break;
        case Options::EMPLOYEE_REMOVE:
            mSelectedEmployeeIndex == 0 ?
                invalidOptionSelected() : removeEmployee();
            /*!
             * Warning: recurssion here!!!
             * This must be considered when doing changes for Options::LANDING
             */
            action(Options::LANDING, nextScreen);
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
    /*!
     * Get the employeeID from employee GUI table
     * Note: mSelectedEmployeeIndex is a 1-based index but vector is zero-based (hence minus 1)
    */
    const std::string& employeeID = mEmployeesGUITable[mSelectedEmployeeIndex - 1].employeeID();
    const entity::Employee& selectedEmployee = mCoreEmployeeMgmt->get(employeeID);
    if (!selectedEmployee.employeeID().empty()) {
        // Valid employee, show the information screen!
        SCREENCOMMON().showTopBanner("Employee Information");
        screen::InformationScreen<entity::Employee> infoScreen(selectedEmployee);
        infoScreen.showBasicInformation();
        infoScreen.showContactDetails();
        infoScreen.showUserAddress();
        infoScreen.showUserPersonalIds();
        infoScreen.showOptions();
    }
}

void EmployeeMgmtScreen::showEmployeesEmptyPopup() {
    std::cout << "Employees record is empty." << std::endl;
}

void EmployeeMgmtScreen::showDataNotReadyScreen() {
    std::cout << "Data is not ready." << std::endl;
}

void EmployeeMgmtScreen::showEmployeeNotFoundPopup() {
    std::cout << "Something went wrong. Please try again." << std::endl;
}

void EmployeeMgmtScreen::showSuccessfullyRemoved(const std::string& id) {
    std::cout << "Successfully removed employee with ID " << id << std::endl;
}

void EmployeeMgmtScreen::showEmployeeExists(const std::string& name) {
    std::cout << "An employee with name: " << name << " also exists. " \
     "Would you like to update that employee instead?" << std::endl;
}

}  // namespace backoffice
}  // namespace screen
