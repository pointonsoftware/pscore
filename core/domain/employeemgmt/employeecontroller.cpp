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
#include "employeecontroller.hpp"
#include <algorithm>
#include <memory>
#include <map>
#include <generator/chargenerator.hpp>
#include <logger/loghelper.hpp>
#include <validator/addressvalidator.hpp>
#include <validator/contactdetailsvalidator.hpp>
#include <validator/employeevalidator.hpp>
#include <validator/personalidvalidator.hpp>
#include <validator/personvalidator.hpp>
#include <validator/uservalidator.hpp>

namespace domain {
namespace empmgmt {

EmployeeMgmtController::EmployeeMgmtController(
                                    const std::shared_ptr<EmployeeMgmtDataInterface>& data,
                                    const std::shared_ptr<EmployeeMgmtViewInterface>& view) {
    if ((data == nullptr) || (view == nullptr)) {
        throw std::invalid_argument("Received a nulltpr argument");
    }
    mDataProvider = data;
    mView = view;
}

std::vector<entity::Employee> EmployeeMgmtController::list() {
    LOG_DEBUG("Getting the list of employees");
    mCachedList = mDataProvider->getEmployees();
    if (mCachedList.empty()) {
        LOG_WARN("There are no employees on record");
        mView->showEmployeesEmptyPopup();
        return {};
    }
    LOG_INFO("Successfully retrieved employees list. Size: %d", mCachedList.size());
    return mCachedList;
}

entity::Employee EmployeeMgmtController::get(const std::string& id) {
    LOG_DEBUG("Getting employee %s", id.c_str());
    const std::vector<entity::Employee>::iterator& iter = find(id);
    if (iter != mCachedList.end()) {
        LOG_INFO("Found employee %s", id.c_str());
        return *iter;
    } else {
        LOG_ERROR("Employee was not found");
        return entity::Employee{};
    }
}

void EmployeeMgmtController::create(const SaveEmployeeData& data) {
    const entity::Employee& newEmployee = data.employee;
    LOG_DEBUG("EmployeeID %s generated", newEmployee.employeeID().c_str());
    // Adding new employee
    mDataProvider->create(newEmployee);
    /*!
     * Todo (code) - add checking if create is successful from dataprovider
     * before updating the cache
    */
    mCachedList.emplace_back(newEmployee);
    LOG_INFO("Employee %s %s added", newEmployee.firstName().c_str(),
                                     newEmployee.lastName().c_str());
    if (newEmployee.isSystemUser()) {
        // Adding new user
        createUser(newEmployee, data.PIN);
    }
}

void EmployeeMgmtController::createUser(const entity::Employee& employee,
                                        const std::string& pin) const {
    entity::User newUser(
        // Todo (code) - need to ensure this ID is unique
        utility::chargenerator::generateUID(employee.firstName(), employee.lastName()),
        employee.position(), pin, employee.employeeID());
    mDataProvider->create(newUser);
    mView->showUserSuccessfullyCreated(employee.firstName(), newUser.userID());
    LOG_INFO("User %s added", newUser.userID().c_str());
}

// Note: Before calling this, make sure the employee is already in the cache list
void EmployeeMgmtController::update(const SaveEmployeeData& data) {
    const entity::Employee& employee = data.employee;
    LOG_DEBUG("Updating employee %s", employee.employeeID().c_str());
    // Update actual data
    mDataProvider->update(employee);
    // If system user, update the user info as well
    if (employee.isSystemUser()) {
        mDataProvider->update(entity::User("Proxy", employee.position(),
                                           "Proxy", employee.employeeID()));
        LOG_INFO("User role updated to %s", employee.position().c_str());
    }
    // Update cache list
    const std::vector<entity::Employee>::iterator it = find(employee.employeeID());
    *it = employee;
    LOG_INFO("Employee %s information updated", employee.employeeID().c_str());
}

USERSMGMTSTATUS EmployeeMgmtController::save(const SaveEmployeeData& employeeData) {
    const entity::Employee& employee = employeeData.employee;
    std::map<std::string, std::string>* validationResult = employeeData.validationResult;
    LOG_DEBUG("Saving employee information");
    if (!validationResult) {
        LOG_ERROR("Validation-message container is not initialized");
        return USERSMGMTSTATUS::UNINITIALIZED;
    }
    // Fill the validation results
    *(validationResult) = validateDetails(employee);
    /*!
     * Todo (code) - the second check will determine if we're creating or updating.
     *               if we're updating, we don't need to validate PIN
     *               until we support User Information update
    */
    if (employee.isSystemUser() && !isExists(employee.employeeID())) {
        // Validate PIN
        entity::validator::UserValidator validator(
                entity::User("Proxy", "Proxy", employeeData.PIN, "Proxy"));
        validationResult->insert(validator.result().begin(), validator.result().end());
    }
    if (!validationResult->empty()) {
        LOG_WARN("Entity contains invalid data. Returning validation results.");
        dumpValidationResult(*(validationResult));
        return USERSMGMTSTATUS::FAILED;
    }
    // Decide if it's a create or update request
    if (isExists(employee.employeeID())) {
        update(employeeData);
    } else {
        create(employeeData);
    }
    return USERSMGMTSTATUS::SUCCESS;
}

USERSMGMTSTATUS EmployeeMgmtController::remove(const std::string& id) {
    LOG_DEBUG("Removing employee with ID %s", id.c_str());
    const std::vector<entity::Employee>::iterator it = find(id);
    if (it == mCachedList.end()) {
        LOG_ERROR("Employee with ID %s was not found in the cache list", id.c_str());
        mView->showDataNotReadyScreen();
        return USERSMGMTSTATUS::NOT_FOUND;
    }
    mDataProvider->removeWithID(id);
    /*!
     * Todo (code) - check if mDataProvider successfully removed the employee
     * E.g. failure: mDataprovider lost db connection
    */
    // Remove from cache
    mCachedList.erase(it);
    mView->showSuccessfullyRemoved(id);
    LOG_INFO("Successfully removed employee with ID %s", id.c_str());
    return USERSMGMTSTATUS::SUCCESS;
}

std::vector<entity::Employee> EmployeeMgmtController::findByName(const std::string& fname,
                                                                 const std::string& lname) {
    /*
     * Todo (code) - look for employees that matches fname
     *             - then check if it matches lname and append to vector
     *             - otherwise, return empty
    */
    return {};
}

bool EmployeeMgmtController::isExists(const std::string& id) {
    return find(id) != mCachedList.end();
}

std::vector<entity::Employee>::iterator EmployeeMgmtController::find(const std::string& id) {
    return std::find_if(mCachedList.begin(), mCachedList.end(), [&id](const entity::Employee& e) {
                return e.employeeID() == id; });
}

ValidationErrors EmployeeMgmtController::validateDetails(const entity::Employee& employee) const {
    ValidationErrors validationErrors;
     // validate key employee data
    {
        entity::validator::EmployeeValidator validator(employee);
        validationErrors.insert(validator.result().begin(), validator.result().end());
    }
    // validate basic information
    {
        entity::validator::PersonValidator validator(employee);
        validationErrors.insert(validator.result().begin(), validator.result().end());
    }
    // validate address
    {
        entity::validator::AddressValidator validator(employee.address());
        validationErrors.insert(validator.result().begin(), validator.result().end());
    }
    // validate contact information
    {
        entity::validator::ContactDetailsValidator validator(employee.contactDetails());
        validationErrors.insert(validator.result().begin(), validator.result().end());
    }
    // validate ID
    {
        for (const entity::PersonalId& personalId : employee.personalIds()) {
            entity::validator::PersonalIDValidator validator(personalId);
            validationErrors.insert(validator.result().begin(), validator.result().end());
        }
    }
    return validationErrors;
}

void EmployeeMgmtController::dumpValidationResult(const ValidationErrors& validationErrors) const {
    LOG_DEBUG("Dumping validation result");
    for (auto const &result : validationErrors) {
        LOG_DEBUG(std::string(result.first + " -> " + result.second).c_str());
    }
}

std::unique_ptr<EmployeeMgmtControlInterface> createEmployeeMgmtModule(
                    const std::shared_ptr<EmployeeMgmtDataInterface>& data,
                    const std::shared_ptr<EmployeeMgmtViewInterface>& view) {
    return std::make_unique<EmployeeMgmtController>(data, view);
}

}  // namespace empmgmt
}  // namespace domain
