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
#include <map>
#include <memory>
#include <string>
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
const std::vector<std::string> DOMAIN_FIELDS {
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
              &entity::Employee::position }), isShowingDetailsScreen(false) {
    // Basic info
    empFieldHelper.addField({entity::FIELD_FNAME, "First Name", &entity::Employee::setFirstName});
    empFieldHelper.addField({entity::FIELD_MNAME, "Middle Name", &entity::Employee::setMiddleName});
    empFieldHelper.addField({entity::FIELD_LNAME, "Last Name", &entity::Employee::setLastName});
    empFieldHelper.addField({entity::FIELD_BDATE, "Birthdate (yyyy/mm/dd)",
                            &entity::Employee::setBirthdate});
    empFieldHelper.addField({entity::FIELD_GENDER, "Gender (M/F)", &entity::Employee::setGender});
    empFieldHelper.addField({entity::FIELD_EPOS, "Position", &entity::Employee::setPosition});
}

void EmployeeMgmtScreen::show(std::promise<defines::display>* promise) {
    mCoreController = domain::empmgmt::createEmployeeMgmtModule(
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
    mTableHelper.setData(mCoreController->list());
}

void EmployeeMgmtScreen::showEmployees() const {
    std::cout << std::endl;
    mTableHelper.printTable();
    SCREENCOMMON().printHorizontalBorder(defines::BORDER_CHARACTER_2);
}

void EmployeeMgmtScreen::showEmployeeInformation(bool showIndex) const {
    /*!
     * Get the employeeID from employee GUI table
     * Note: mSelectedEmployeeIndex is a 1-based index but vector is zero-based (hence minus 1)
    */
    const std::string& employeeID = mTableHelper.getSelectedData().ID();
    const entity::Employee& selectedEmployee = mCoreController->getEmployee(employeeID);
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
        infoScreen.showAddress();
        infoScreen.showContactDetails();
        infoScreen.showPersonalIds();

        // Show user data
        if (selectedEmployee.isSystemUser()) {
            const entity::User& userdata = mCoreController->getUser(employeeID);
            screen::InformationScreen<entity::User> userDataScreen(userdata);
            userDataScreen.showBasicInformation();
        }

        // Options must be at the bottom
        infoScreen.showOptions();
    }
}

void EmployeeMgmtScreen::removeEmployee() {
    if (mCoreController->remove(mTableHelper.getSelectedData().ID())
          == domain::empmgmt::EMPLMGMTSTATUS::SUCCESS) {
       // Remove the user form
       mTableHelper.deleteSelectedData();
    }
}

void EmployeeMgmtScreen::fillOtherEmployeeInformation(entity::Employee* employee,
                         const std::vector<std::string>& requiredFields) const {
    const auto& requires = [&requiredFields](const std::string& field) {
        if (requiredFields.empty()) {
            // All fields are requested by default
            return true;
        }
        return std::find(requiredFields.begin(), requiredFields.end(), field)
                         != requiredFields.end();
    };
    /**
     *  Todo (code) - add support to cancel input request
     *  see: https://github.com/pointonsoftware/pscore/issues/202
     */
    // Address
    {
        entity::Address address = employee->address();
        if (requires("Address.Line1")) {
            address.line1 = SCREENCOMMON().getInput("Address 1");
        }
        if (requires("Address.Line2")) {
            address.line2 = SCREENCOMMON().getInput("Address 2");
        }
        if (requires("Address.CityTown")) {
            address.city_town = SCREENCOMMON().getInput("City/Town");
        }
        if (requires("Address.Province")) {
            address.province = SCREENCOMMON().getInput("Province");
        }
        if (requires("Address.Zip")) {
            address.zip = SCREENCOMMON().getInput("Zip");
        }
        employee->setAddress(address);
    }
    // Contact details
    {
        entity::ContactDetails contactDetails = employee->contactDetails();
        if (requires("ContactDetails.Phone1")) {
            contactDetails.phone_number_1 = SCREENCOMMON().getInput("Phone Number 1");
        }
        if (requires("ContactDetails.Phone2")) {
            contactDetails.phone_number_2 = SCREENCOMMON().getInput("Phone Number 2");
        }
        if (requires("ContactDetails.Email")) {
            contactDetails.email = SCREENCOMMON().getInput("Email Address");
        }
        employee->setPhoneNumbers(contactDetails.phone_number_1, contactDetails.phone_number_2);
        employee->setEmail(contactDetails.email);
    }
    // Ask if user wants to input a valid/government ID
    if (requires("PersonalId.Type") || requires("PersonalId.Number")) {
        entity::PersonalId personalId;
        // We're creating a new employee, ask if the employee has a Valid ID
        bool idFieldsRequired = SCREENCOMMON().getYesNoInput("Has government ID (y/n)") == "y";

        if (idFieldsRequired) {
            if (requires("PersonalId.Type")) {
                personalId.type = SCREENCOMMON().getInput("ID Type");
            }
            if (requires("PersonalId.Number")) {
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
    entity::Employee newEmployee(app::util::generateEmployeeID());
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
        empFieldHelper.getInputsFromField(&newEmployee, failedFields);
        if (empFieldHelper.isBreak()) {
            // User requested to cancel
            break;
        }
        fillOtherEmployeeInformation(&newEmployee, failedFields);
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
                return mCoreController->save({newEmployee, "", &validationResult});
            } else {
                // Employee is a system user
                newEmployee.setIsSystemUser(true);
                // User PIN
                const std::string pin = SCREENCOMMON().getInput("PIN");
                return mCoreController->save({newEmployee, pin, &validationResult});
            }
        }();

        // Reset after filling the fields
        failedFields.clear();

        if (status != domain::empmgmt::EMPLMGMTSTATUS::SUCCESS) {
            failedFields = app::util::extractMapKeys(validationResult);
            SCREENCOMMON().printErrorList(app::util::extractMapValues(validationResult));
        } else {
            std::cout << "Employee " << newEmployee.getFullName()
                      << " added successfully!" << std::endl;
        }
    } while (!failedFields.empty());  // repeat input until new employee is created
}

void EmployeeMgmtScreen::updateEmployee() {
    showEmployeeInformation(true);  // true - request to show the index # of each data
    // Get the field to update
    const std::string field = SCREENCOMMON().getUpdateField(DOMAIN_FIELDS);
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
            empFieldHelper.getInputsFromField(&updateEmployee, requiredFields);
            if (empFieldHelper.isBreak()) {
                // User requested to cancel
                break;
            }
            fillOtherEmployeeInformation(&updateEmployee, requiredFields);
            // Reset validation results
            validationResult.clear();
            if (mCoreController->save({updateEmployee, "", &validationResult}) !=
                domain::empmgmt::EMPLMGMTSTATUS::SUCCESS) {
                requiredFields = app::util::extractMapKeys(validationResult);
                SCREENCOMMON().printErrorList(app::util::extractMapValues(validationResult));
            } else {
                mTableHelper.setData((mTableHelper.getCurrentIndex()), updateEmployee);
            }
        } while (!validationResult.empty());  // repeat input until data is updated
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
            return Options::OP_READ;
        }
    } else if (userInput == "c" && !isShowingDetailsScreen) {
        return Options::OP_CREATE;
    } else if (userInput == "u" && isShowingDetailsScreen) {
        return Options::OP_UPDATE;
    } else if (userInput == "d" && isShowingDetailsScreen) {
        return Options::OP_DELETE;
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
        case Options::OP_READ:
            showEmployeeInformation();
            isShowingDetailsScreen = true;  // Must set to true
            break;
        case Options::OP_CREATE:
            createEmployee();
            // Get the employees from Core then cache the list
            queryEmployeesList();
            showLandingScreen();
            break;
        case Options::OP_UPDATE:
            updateEmployee();
            showEmployeeInformation();  // refresh employee details screen
            break;
        case Options::OP_DELETE:
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
