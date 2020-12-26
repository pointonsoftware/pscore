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
#include <map>
#include <vector>
#include <general.hpp>  // pscore utility
// view
#include <idgenerator.hpp>
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

void EmployeeMgmtScreen::fillEmployeeInformation(entity::Employee* employee,
                         const std::vector<std::string>& requiredFields) const {
    ScreenInterface::FieldHelper fieldHelper(requiredFields);
    // Basic info
    inputArea(std::bind(&entity::Employee::setFirstName, employee, std::placeholders::_1),
              "First Name", fieldHelper.requires("Person.First.Name"));
    inputArea(std::bind(&entity::Employee::setMiddleName, employee, std::placeholders::_1),
              "Middle Name", fieldHelper.requires("Person.Middle.Name"));
    inputArea(std::bind(&entity::Employee::setLastName, employee, std::placeholders::_1),
              "Last Name", fieldHelper.requires("Person.Last.Name"));
    inputArea(std::bind(&entity::Employee::setBirthdate, employee, std::placeholders::_1),
              "Date of Birth (dd/mm/yyyy)", fieldHelper.requires("Person.Birthdate"));
    inputArea(std::bind(&entity::Employee::setGender, employee, std::placeholders::_1),
              "Gender (M/F)", fieldHelper.requires("Person.Gender"));
    inputArea(std::bind(&entity::Employee::setPosition, employee, std::placeholders::_1),
              "Position", fieldHelper.requires("Employee.Position"));
    // Address
    {
        entity::Address address = employee->address();
        if (fieldHelper.requires("Address.Line1")) {
            address.line1 = SCREENCOMMON().getInput("Address 1");
        }
        if (fieldHelper.requires("Address.Line2")) {
            address.line2 = SCREENCOMMON().getInput("Address 2");
        }
        if (fieldHelper.requires("Address.CityTown")) {
            address.city_town = SCREENCOMMON().getInput("City/Town");
        }
        if (fieldHelper.requires("Address.Province")) {
            address.province = SCREENCOMMON().getInput("Province");
        }
        if (fieldHelper.requires("Address.Zip")) {
            address.zip = SCREENCOMMON().getInput("Zip");
        }
        employee->setAddress(address);
    }
    // Contact details
    {
        entity::ContactDetails contactDetails = employee->contactDetails();
        if (fieldHelper.requires("ContactDetails.Phone1")) {
            contactDetails.phone_number_1 = SCREENCOMMON().getInput("Phone Number 1");
        }
        if (fieldHelper.requires("ContactDetails.Phone2")) {
            contactDetails.phone_number_2 = SCREENCOMMON().getInput("Phone Number 2");
        }
        if (fieldHelper.requires("ContactDetails.Email")) {
            contactDetails.email = SCREENCOMMON().getInput("Email Address");
        }
        employee->setPhoneNumbers(contactDetails.phone_number_1, contactDetails.phone_number_2);
        employee->setEmail(contactDetails.email);
    }
    // Ask if user wants to input a valid/government ID
    if (fieldHelper.requires("PersonalId.Type") || fieldHelper.requires("PersonalId.Number")) {
        entity::PersonalId personalId;
        bool idFieldsRequired = true;
        bool updateFields = false;

        if (requiredFields.empty()) {
            // Ask if user has a Valid ID
            idFieldsRequired = SCREENCOMMON().getYesNoInput("Has valid/government ID (y/n)") == "y";
        } else {
            // WARNING! - this is assumming we're updating the first element of personalIds
            personalId = employee->personalIds()[0];
            updateFields = true;
        }

        if (idFieldsRequired) {
            if (fieldHelper.requires("PersonalId.Type")) {
                personalId.type = SCREENCOMMON().getInput("ID Type");
            }
            if (fieldHelper.requires("PersonalId.Number")) {
                personalId.id_number = SCREENCOMMON().getInput("ID Number");
            }
            if (updateFields) {
                // Delete the old id
                // WARNING! - this is assumming we're updating the first element of personalIds
                employee->deletePersonalId(0);
            }
            // Add a new one
            employee->addPersonalId(personalId.type, personalId.id_number);
        }
    }
}

void EmployeeMgmtScreen::createEmployee() {
    SCREENCOMMON().showTopBanner("Create Employee");
    std::cout << "Type [space] for an empty entry" << std::endl;
    std::vector<std::string> failedFields;  // Used to request re-input of failed fields
    // App must provide the employee ID
    entity::Employee newEmployee(app::utility::generateEmployeeID());
    // Todo (code) - let's default to ACTIVE for now
    newEmployee.setStatus("ACTIVE");
    /*!
     * Todo (code)
     * - do findByName(fname, lname) first
     * - if found, show "An employee name Foo Bar with ID xxxx exists,
     *                   do you want to update this employee instead?"
    */
    do {
        std::map<std::string, std::string> validationResult;
        fillEmployeeInformation(&newEmployee, failedFields);
        const domain::empmgmt::EMPLMGMTSTATUS status =
            [this, &newEmployee, &validationResult, &failedFields]() {
            const bool isSystemUser = [&newEmployee, &failedFields]() {
                if (newEmployee.isSystemUser()) {
                    return true;
                }
                if (failedFields.empty()) {
                    // We're not editing the PIN field, ask if employee is a system user
                    return SCREENCOMMON().getYesNoInput("System User (y/n)") == "y";
                }
                // Check if we require re-input for PIN field
                // If so, we're editing a system user entity
                return std::find(failedFields.begin(), failedFields.end(),
                                 "User.Pin") != failedFields.end();
            }();

            if (!isSystemUser) {
                // non-user, add the employee
                return mCoreEmployeeMgmt->save({newEmployee, "", &validationResult});
            } else {
                // Employee is a system user
                newEmployee.setIsSystemUser(true);
                // User PIN
                const std::string pin = SCREENCOMMON().getInput("PIN");
                return mCoreEmployeeMgmt->save({newEmployee, pin, &validationResult});
            }
        }();

        // Reset after filling the fields
        failedFields.clear();

        if (status != domain::empmgmt::EMPLMGMTSTATUS::SUCCESS) {
            std::cout << "Invalid inputs:" << std::endl;
            for (auto const &result : validationResult) {
                std::cout << "- " << result.second << std::endl;
                failedFields.emplace_back(result.first);
            }
            // Let the user confirm after viewing the validation results
            std::cout << "Press [Enter] to update fields..." << std::endl;
            std::cin.ignore();
            std::cin.get();
        } else {
            std::cout << "Employee " << newEmployee.getFullName()
                      << " added successfully!" << std::endl;
        }
    } while (!failedFields.empty());  // repeat input until new employee is created
}

void EmployeeMgmtScreen::updateEmployee() {
    showEmployeeInformation(true);  // true - request to show the index # of each data
    // Get the field to update
    const std::string field = [this]() {
        unsigned int index;
        do {
            // Ask the index from the user
            std::string userInput = SCREENCOMMON().getInput("Input the data [number] to edit");
            if (utility::isNumber(userInput)) {
                index =  std::stoi(userInput);
                break;
            }
         } while (1);  // Keep asking until a number is inputted
        // Fetch the selected field
        return getEntityField(index);
    }();
    if (field.empty()) {
        std::cout << "Invalid selection." << std::endl;
        return;
    }
    {   // Update operation
        std::vector<std::string> requiredFields = { field };
        std::map<std::string, std::string> validationResult;
        entity::Employee updateEmployee = mEmployeesGUITable[mSelectedEmployeeIndex - 1];
        do {
            fillEmployeeInformation(&updateEmployee, requiredFields);
            // Reset validation results
            validationResult.clear();
            if (mCoreEmployeeMgmt->save({updateEmployee, "", &validationResult}) !=
                domain::empmgmt::EMPLMGMTSTATUS::SUCCESS) {
                for (auto const &result : validationResult) {
                    std::cout << "- " << result.second << std::endl;
                }
                // Let the user confirm after viewing the validation results
                std::cout << "Press [Enter] to update fields..." << std::endl;
                std::cin.ignore();
                std::cin.get();
            }
        } while (!validationResult.empty());  // repeat input until new employee is created
        mEmployeesGUITable[mSelectedEmployeeIndex - 1] = updateEmployee;
    }
    showEmployeeInformation();  // refresh employee details screen
}

void EmployeeMgmtScreen::removeEmployee() {
    if (mCoreEmployeeMgmt->remove(mEmployeesGUITable[mSelectedEmployeeIndex - 1].ID())
          == domain::empmgmt::EMPLMGMTSTATUS::SUCCESS) {
       // Remove the user form
       mEmployeesGUITable.erase(mEmployeesGUITable.begin() + (mSelectedEmployeeIndex - 1));
    }
}

const std::string EmployeeMgmtScreen::getEntityField(unsigned int index) const {
    static const std::vector<std::string> employeeDomainFields {
        "Person.First.Name",
        "Person.Middle.Name",
        "Person.Last.Name",
        "Person.Birthdate",
        "Person.Gender",
        "Employee.Position",
        "Address.Line1",
        "Address.Line2",
        "Address.CityTown",
        "Address.Province",
        "Address.Zip",
        "ContactDetails.Phone1",
        "ContactDetails.Phone2",
        "ContactDetails.Email",
        "PersonalId.Type",
        "PersonalId.Number"
    };
    if (index >= employeeDomainFields.size()) {
        return "";
    }
    // Vector is a 0-based index
    return employeeDomainFields[index - 1];
}

void EmployeeMgmtScreen::showEmployees() const {
    std::cout << std::endl;
    // Display the columns
    SCREENCOMMON().printColumns({"Employee ID", "First Name", "Last Name", "Position"}, true);
    // Display employees
    for (unsigned int index = 0; index < mEmployeesGUITable.size(); ++index) {
        SCREENCOMMON().printColumns({
            std::string("[" + std::to_string(index + 1) + "] "
                         + mEmployeesGUITable[index].ID()),
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
        // We should return whatever was the previous screen
        // For now, we will check if user has selected an index (i.e. info screen is shown)
        if (mSelectedEmployeeIndex == 0) {
            return Options::DASHBOARD;
        }
        return Options::LANDING;
    } else if (userInput == "0") {
        return Options::LOGOUT;
    } else if (utility::isNumber(userInput)) {
        /*!
         * If the input is a number, check if we're in the landing screen.
         * If we're currently in the landing screen, go to employee details.
         * Otherwise, return invalid.
        */
        if (mSelectedEmployeeIndex == 0) {
            // Store user input as the selected index
            mSelectedEmployeeIndex = std::stoi(userInput);
            return Options::EMPLOYEE_DETAILS;
        }
    } else if (userInput == "c") {
        return Options::EMPLOYEE_CREATE;
    } else if (userInput == "u") {
        return Options::EMPLOYEE_UPDATE;
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
            // Warning! Consider the recurssion in EMPLOYEE_REMOVE when making changes
            mSelectedEmployeeIndex = 0;  // reset whenever we go to landing
            showLandingScreen();
            break;
        case Options::INVALID:
            invalidOptionSelected();
            break;
        case Options::EMPLOYEE_DETAILS:
            if (mSelectedEmployeeIndex > (mEmployeesGUITable.size())) {
                 mSelectedEmployeeIndex = 0;  // reset while we're in the landing screen
                invalidOptionSelected();
            } else {
                showEmployeeInformation();
            }
            break;
        case Options::EMPLOYEE_CREATE:
            createEmployee();
            // Get the employees from Core then cache the list
            queryEmployeesList();
            showLandingScreen();
            break;
        case Options::EMPLOYEE_UPDATE:
            // Make sure an employee was selected from the list
            mSelectedEmployeeIndex == 0 ?
                invalidOptionSelected() : updateEmployee();
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

void EmployeeMgmtScreen::showEmployeeInformation(bool showIndex) const {
    /*!
     * Get the employeeID from employee GUI table
     * Note: mSelectedEmployeeIndex is a 1-based index but vector is zero-based (hence minus 1)
    */
    const std::string& employeeID = mEmployeesGUITable[mSelectedEmployeeIndex - 1].ID();
    const entity::Employee& selectedEmployee = mCoreEmployeeMgmt->get(employeeID);
    if (!selectedEmployee.ID().empty()) {
        // Valid employee, show the information screen!
        SCREENCOMMON().showTopBanner("Employee Information");
        screen::InformationScreen<entity::Employee> infoScreen(selectedEmployee);
        infoScreen.showItemIndex(showIndex);
        /*!
         * The sequence of calls below to InformationScreen should be in-sync with
         * the entity fields in EmployeeMgmtScreen::getEntityField()
        */
        infoScreen.showBasicInformation();
        infoScreen.showUserAddress();
        infoScreen.showContactDetails();
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

void EmployeeMgmtScreen::showUserSuccessfullyCreated(const std::string& name,
                                                     const std::string& userID) {
    std::cout << std::endl << "Welcome, " << name << "! "
              << "Please take note of your Login ID: " << userID << std::endl;
    // Let the user confirm
    std::cin.ignore();
    std::cin.get();
}

}  // namespace backoffice
}  // namespace screen
