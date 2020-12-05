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
    // All fields are required by default
    const bool isAllFieldsRequired = requiredFields.empty();
    // Find the field from the "requiredFields" vector
    auto requires = [requiredFields, isAllFieldsRequired](const std::string& field) {
        if (!isAllFieldsRequired) {
            return std::find(requiredFields.begin(), requiredFields.end(), field)
                != requiredFields.end();
        }
        return true;
    };
    // Simulate an input area or text box of GUI
    auto inputArea = [isAllFieldsRequired] (std::function<void(const std::string&)> func,
                                            const std::string& label, bool fieldIsRequired) {
        if (fieldIsRequired) {
            func(SCREENCOMMON().getInput(label));
        }
    };
    // Basic info
    inputArea(std::bind(&entity::Employee::setFirstName, employee,
              std::placeholders::_1), "First Name", requires("Entity.Field.FirstName"));
    inputArea(std::bind(&entity::Employee::setMiddleName, employee,
              std::placeholders::_1), "Middle Name", requires("Entity.Field.MiddleName"));
    inputArea(std::bind(&entity::Employee::setLastName, employee,
              std::placeholders::_1), "Last Name", requires("Entity.Field.LastName"));
    inputArea(std::bind(&entity::Employee::setBirthdate, employee,
              std::placeholders::_1), "Date of Birth (dd/mm/yyyy)",
                                      requires("Entity.Field.Birthdate"));
    inputArea(std::bind(&entity::Employee::setGender, employee,
              std::placeholders::_1), "Gender (M/F)", requires("Entity.Field.Gender"));
    inputArea(std::bind(&entity::Employee::setPosition, employee,
              std::placeholders::_1), "Position", requires("Entity.Field.Position"));
    // Address
    {
        entity::Address address = employee->address();
        if (requires("Entity.Field.HouseNumber")) {
            address.housenumber = SCREENCOMMON().getInput("House Number");
        }
        if (requires("Entity.Field.Lot")) {
            address.lot = SCREENCOMMON().getInput("Lot Number");
        }
        if (requires("Entity.Field.Block")) {
            address.block = SCREENCOMMON().getInput("Block");
        }
        if (requires("Entity.Field.Street")) {
            address.street = SCREENCOMMON().getInput("Street");
        }
        if (requires("Entity.Field.Subdivision")) {
            address.subdivision = SCREENCOMMON().getInput("Subdivision");
        }
        if (requires("Entity.Field.Sitio")) {
            address.sitio = SCREENCOMMON().getInput("Sitio");
        }
        if (requires("Entity.Field.Purok")) {
            address.purok = SCREENCOMMON().getInput("Purok");
        }
        if (requires("Entity.Field.Barangay")) {
            address.barangay = SCREENCOMMON().getInput("Barangay");
        }
        if (requires("Entity.Field.CityTown")) {
            address.city_town = SCREENCOMMON().getInput("City/Town");
        }
        if (requires("Entity.Field.Province")) {
            address.province = SCREENCOMMON().getInput("Province");
        }
        if (requires("Entity.Field.Zip")) {
            address.zip = SCREENCOMMON().getInput("Zip");
        }
        employee->setAddress(address);
    }
    // Contact details
    {
        entity::ContactDetails contactDetails = employee->contactDetails();
        if (requires("Entity.Field.Phone1")) {
            contactDetails.phone_number_1 = SCREENCOMMON().getInput("Phone Number 1");
        }
        if (requires("Entity.Field.Phone2")) {
            contactDetails.phone_number_2 = SCREENCOMMON().getInput("Phone Number 2");
        }
        if (requires("Entity.Field.Email")) {
            contactDetails.email = SCREENCOMMON().getInput("Email Address");
        }
        employee->setPhoneNumbers(contactDetails.phone_number_1, contactDetails.phone_number_2);
        employee->setEmail(contactDetails.email);
    }
    // Ask if user wants to input a valid/government ID
    if (requires("Entity.Field.IdType") || requires("Entity.Field.IdNumber")) {
        entity::PersonalId personalId;
        bool idFieldsRequired = true;
        bool updateFields = false;

        if (isAllFieldsRequired) {
            // Ask if user has a Valid ID
            idFieldsRequired = SCREENCOMMON().getYesNoInput("Has valid/government ID (y/n)") == "y";
        } else {
            // WARNING! - this is assumming we're updating the first element of personalIds
            personalId = employee->personalIds()[0];
            updateFields = true;
        }

        if (idFieldsRequired) {
            if (requires("Entity.Field.IdType")) {
                personalId.type = SCREENCOMMON().getInput("ID Type");
            }
            if (requires("Entity.Field.IdNumber")) {
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
    std::cout << std::endl << "Add Employee - type [space] for empty entry" << std::endl;
    std::map<std::string, std::string> validationResult;
    std::vector<std::string> failedFields;  // Used to request re-input of failed fields
    entity::Employee* newEmployee = new entity::Employee();
    /*!
     * Todo (code)
     * - do findByName(fname, lname) first
     * - if found, show "An employee name Foo Bar with ID xxxx exists,
     *                   do you want to update this employee instead?"
    */
    do {
        fillEmployeeInformation(newEmployee, failedFields);
        const domain::empmgmt::USERSMGMTSTATUS status =
            [this, &newEmployee, &validationResult, &failedFields]() {
            const bool isSystemUser = [&newEmployee, &failedFields]() {
                if (newEmployee->isSystemUser()) {
                    return true;
                }
                if (failedFields.empty()) {
                    // We're not editing the PIN field, ask if employee is a system user
                    return SCREENCOMMON().getYesNoInput("System User (y/n)") == "y";
                }
                // Check if we require re-input for PIN field
                // If so, we're editing a system user entity
                return std::find(failedFields.begin(), failedFields.end(),
                                 "Entity.Field.Pin") != failedFields.end();
            }();

            if (!isSystemUser) {
                // non-user, add the employee
                return mCoreEmployeeMgmt->save({*newEmployee, "", &validationResult});
            } else {
                // Employee is a system user
                newEmployee->setIsSystemUser(true);
                // User PIN
                const std::string pin = SCREENCOMMON().getInput("PIN");
                return mCoreEmployeeMgmt->save({*newEmployee, pin, &validationResult});
            }
        }();

        // Reset after filling the fields
        failedFields.clear();

        if (status != domain::empmgmt::USERSMGMTSTATUS::SUCCESS) {
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
            std::cout << "Employee " << newEmployee->getFullName()
                    << " added successfully!" << std::endl;
        }
    } while (!failedFields.empty());  // repeat input until new employee is created
    // delete the heap object
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
