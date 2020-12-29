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
#include <fieldhelper.hpp>
#include <generalhelper.hpp>  // view utility
#include <informationscreen.hpp>
#include <screencommon.hpp>

namespace screen {
namespace backoffice {

// Employee fields
const std::vector<std::string> EmployeeMgmtScreen::employeeDomainFields {
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

EmployeeMgmtScreen::EmployeeMgmtScreen()
    : mTableHelper({"Employee ID", "First Name", "Last Name", "Position"},
            { &entity::Employee::ID, &entity::Employee::firstName, &entity::Employee::lastName,
              &entity::Employee::position }), isShowingDetailsScreen(false) {}

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
    mTableHelper.setData(mCoreEmployeeMgmt->list());
}

void EmployeeMgmtScreen::showEmployees() const {
    std::cout << std::endl;
    mTableHelper.printTable();
    SCREENCOMMON().printHorizontalBorder(defines::BORDER_CHARACTER_2);
}

void EmployeeMgmtScreen::showOptions() const {
    std::cout << std::endl << std::endl;
    SCREENCOMMON().printColumns({"[b] - Back", "[c] - Create", "[0] - Logout"},
                                 true, false);
    std::cout << std::endl;
}

void EmployeeMgmtScreen::showEmployeeInformation(bool showIndex) const {
    /*!
     * Get the employeeID from employee GUI table
     * Note: mSelectedEmployeeIndex is a 1-based index but vector is zero-based (hence minus 1)
    */
    const std::string& employeeID = mTableHelper.getSelectedData().ID();
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

void EmployeeMgmtScreen::removeEmployee() {
    if (mCoreEmployeeMgmt->remove(mTableHelper.getSelectedData().ID())
          == domain::empmgmt::EMPLMGMTSTATUS::SUCCESS) {
       // Remove the user form
       mTableHelper.deleteSelectedData();
    }
}

void EmployeeMgmtScreen::fillEmployeeInformation(entity::Employee* employee,
                         const std::vector<std::string>& requiredFields) const {
    app::utility::FieldHelper fieldHelper(requiredFields);
    // Basic info
    SCREENCOMMON().inputArea(std::bind(&entity::Employee::setFirstName, employee,
        std::placeholders::_1), "First Name", fieldHelper.requires("Person.First.Name"));
    SCREENCOMMON().inputArea(std::bind(&entity::Employee::setMiddleName, employee,
        std::placeholders::_1), "Middle Name", fieldHelper.requires("Person.Middle.Name"));
    SCREENCOMMON().inputArea(std::bind(&entity::Employee::setLastName, employee,
        std::placeholders::_1), "Last Name", fieldHelper.requires("Person.Last.Name"));
    SCREENCOMMON().inputArea(std::bind(&entity::Employee::setBirthdate, employee,
        std::placeholders::_1), "Birthdate (dd/mm/yyyy)", fieldHelper.requires("Person.Birthdate"));
    SCREENCOMMON().inputArea(std::bind(&entity::Employee::setGender, employee,
        std::placeholders::_1), "Gender (M/F)", fieldHelper.requires("Person.Gender"));
    SCREENCOMMON().inputArea(std::bind(&entity::Employee::setPosition, employee,
        std::placeholders::_1), "Position", fieldHelper.requires("Employee.Position"));
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
        // We're creating a new employee, ask if the employee has a Valid ID
        bool idFieldsRequired = SCREENCOMMON().getYesNoInput("Has government ID (y/n)") == "y";

        if (idFieldsRequired) {
            if (fieldHelper.requires("PersonalId.Type")) {
                personalId.type = SCREENCOMMON().getInput("ID Type");
            }
            if (fieldHelper.requires("PersonalId.Number")) {
                personalId.id_number = SCREENCOMMON().getInput("ID Number");
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
            failedFields = app::utility::extractMapKeys(validationResult);
            SCREENCOMMON().printErrorList(app::utility::extractMapValues(validationResult));
        } else {
            std::cout << "Employee " << newEmployee.getFullName()
                      << " added successfully!" << std::endl;
        }
    } while (!failedFields.empty());  // repeat input until new employee is created
}

void EmployeeMgmtScreen::updateEmployee() {
    showEmployeeInformation(true);  // true - request to show the index # of each data
    // Get the field to update
    const std::string field = SCREENCOMMON().getUpdateField(employeeDomainFields);
    if (field.empty()) {
        std::cout << "Invalid selection." << std::endl;
        return;
    }
    // We currently don't support updating the Personal ID field due to code complexity
    // Track - https://github.com/pointonsoftware/pscore/issues/106
    if ((field == "PersonalId.Type") || (field == "PersonalId.Number")) {
        std::cout << "Invalid selection." << std::endl;
        return;
    }
    {   // Update operation
        std::vector<std::string> requiredFields = { field };
        std::map<std::string, std::string> validationResult;
        entity::Employee updateEmployee = mTableHelper.getSelectedData();
        do {
            fillEmployeeInformation(&updateEmployee, requiredFields);
            // Reset validation results
            validationResult.clear();
            if (mCoreEmployeeMgmt->save({updateEmployee, "", &validationResult}) !=
                domain::empmgmt::EMPLMGMTSTATUS::SUCCESS) {
                requiredFields = app::utility::extractMapKeys(validationResult);
                SCREENCOMMON().printErrorList(app::utility::extractMapValues(validationResult));
            }
        } while (!validationResult.empty());  // repeat input until new employee is created
        mTableHelper.setData((mTableHelper.getCurrentIndex()), updateEmployee);
    }
}

EmployeeMgmtScreen::Options EmployeeMgmtScreen::getUserSelection() {
    std::string userInput;
    std::cout << std::endl << "Select [option] > "; std::cin >> userInput;

    if (userInput == "x") {
        return Options::APP_EXIT;
    } else if (userInput == "b") {
        // We should return whatever was the previous screen
        // For now, we will check if the info screen is shown
        return isShowingDetailsScreen ? Options::LANDING : Options::DASHBOARD;
    } else if (userInput == "0") {
        return Options::LOGOUT;
    } else if (utility::isNumber(userInput) && !isShowingDetailsScreen) {
        // Check if input is within the valid indexes
        uint8_t input = std::stoi(userInput) - 1;
        if (input < mTableHelper.getDataCount()) {
            // Store user input as the selected index (zero based)
            mTableHelper.setCurrentIndex(input);
            return Options::EMPLOYEE_DETAILS;
        }
    } else if (userInput == "c" && !isShowingDetailsScreen) {
        return Options::EMPLOYEE_CREATE;
    } else if (userInput == "u" && isShowingDetailsScreen) {
        return Options::EMPLOYEE_UPDATE;
    } else if (userInput == "d" && isShowingDetailsScreen) {
        return Options::EMPLOYEE_REMOVE;
    }  // add more options here

    // Default invalid option
    return Options::INVALID;
}

bool EmployeeMgmtScreen::action(Options option, std::promise<defines::display>* nextScreen) {
    bool switchScreenIsRequired = false;
    switch (option) {
        case Options::LANDING:
            // Warning: There are recurssions inside this switch-case()
            // These must be considered when doing changes for Options::LANDING
            queryEmployeesList();
            showLandingScreen();
            isShowingDetailsScreen = false;  // Must set to false
            break;
        case Options::INVALID:
            invalidOptionSelected();
            break;
        case Options::EMPLOYEE_DETAILS:
            showEmployeeInformation();
            isShowingDetailsScreen = true;  // Must set to true
            break;
        case Options::EMPLOYEE_CREATE:
            createEmployee();
            // Get the employees from Core then cache the list
            queryEmployeesList();
            showLandingScreen();
            break;
        case Options::EMPLOYEE_UPDATE:
            updateEmployee();
            showEmployeeInformation();  // refresh employee details screen
            break;
        case Options::EMPLOYEE_REMOVE:
            removeEmployee();
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
