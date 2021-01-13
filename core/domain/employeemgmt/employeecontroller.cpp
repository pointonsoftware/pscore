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
#include <general.hpp>  // pscore utility
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

EmployeeMgmtController::EmployeeMgmtController(const EmpMgmtDataPtr& data,
                                               const EmpMgmtViewPtr& view) {
    if ((data == nullptr) || (view == nullptr)) {
        throw std::invalid_argument("Received a nulltpr argument");
    }
    mDataProvider = data;
    mView = view;
}

std::vector<entity::Employee> EmployeeMgmtController::list() {
    LOG_DEBUG("Getting the list of employees");
    mCachedList.fill(mDataProvider->getEmployees());
    if (!mCachedList.hasData()) {
        LOG_WARN("There are no employees on record");
        mView->showEmployeesEmptyPopup();
        return {};
    }
    LOG_INFO("Successfully retrieved employees list. Size: %d", mCachedList.dataCount());
    return mCachedList.get();
}

entity::Employee EmployeeMgmtController::getEmployee(const std::string& employeeID) {
    LOG_DEBUG("Getting employee %s", employeeID.c_str());
    const std::vector<entity::Employee>::iterator& iter =
                     mCachedList.find(employeeID, &entity::Employee::ID);
    if (iter == mCachedList.endOfData()) {
        LOG_ERROR("Employee was not found");
        return entity::Employee{};
    }
    LOG_INFO("Found employee %s", employeeID.c_str());
    return *iter;
}

entity::User EmployeeMgmtController::getUser(const std::string& employeeID) {
    LOG_DEBUG("Retrieving user data of %s", employeeID.c_str());
    const entity::User& user = mDataProvider->getUserData(employeeID);
    // Todo - add a check if data provider operation was successful
    if (user.userID().empty() || (user.employeeID() != employeeID)) {
        LOG_ERROR("User was not found");
        return entity::User();
    }
    LOG_INFO("Found user %s data.", user.userID().c_str());
    return user;
}

void EmployeeMgmtController::create(const SaveEmployeeData& data) {
    const entity::Employee& newEmployee = data.employee;
    LOG_DEBUG("Creating employee %s", newEmployee.ID().c_str());
    // Adding new employee
    mDataProvider->create(newEmployee);
    /*!
     * Todo (code) - add checking if create is successful from dataprovider
     * before updating the cache
    */
    mCachedList.insert(newEmployee);
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
        employee.position(), pin, utility::currentDateTime(), employee.ID());
    mDataProvider->create(newUser);
    mView->showUserSuccessfullyCreated(employee.firstName(), newUser.userID());
    LOG_INFO("User %s added", newUser.userID().c_str());
}

// Note: Before calling this, make sure the employee is already in the cache list
void EmployeeMgmtController::update(const SaveEmployeeData& data) {
    const entity::Employee& employee = data.employee;
    LOG_DEBUG("Updating employee %s", employee.ID().c_str());
    // Update actual data
    mDataProvider->update(employee);
    // If system user, update the user info as well
    if (employee.isSystemUser()) {
        mDataProvider->update(entity::User("Proxy", employee.position(),
                                           "Proxy", "Proxy", employee.ID()));
        LOG_INFO("User role updated to %s", employee.position().c_str());
    }
    // Update cache list
    const std::vector<entity::Employee>::iterator it =
                     mCachedList.find(employee.ID(), &entity::Employee::ID);
    *it = employee;
    LOG_INFO("Employee %s information updated", employee.ID().c_str());
}

EMPLMGMTSTATUS EmployeeMgmtController::save(const SaveEmployeeData& employeeData) {
    const entity::Employee& employee = employeeData.employee;
    LOG_DEBUG("Saving employee information");
    if (!employeeData.validationResult) {
        LOG_ERROR("Validation-message container is not initialized");
        return EMPLMGMTSTATUS::UNINITIALIZED;
    }
    // Cleanup the container
    employeeData.validationResult->clear();
    // Fill the validation results
    *(employeeData.validationResult) = validateDetails(employee);
    /*!
     * Todo (code) - the second check will determine if we're creating or updating.
     *               if we're updating, we don't need to validate PIN
     *               until we support User Information update
    */
    if (employee.isSystemUser() &&
        !mCachedList.isExists(employee.ID(), &entity::Employee::ID)) {
        // Validate PIN only
        entity::validator::UserValidator validator(
                entity::User("Proxy", "Proxy", employeeData.PIN,
                             "2020/10/10 10:10:10", "Proxy"));
        employeeData.validationResult->merge(validator.result());
    }
    if (!employeeData.validationResult->empty()) {
        LOG_WARN("Entity contains invalid data. Returning validation results.");
        dumpValidationResult(*(employeeData.validationResult));
        return EMPLMGMTSTATUS::FAILED;
    }
    // Decide if it's a create or update request
    if (mCachedList.isExists(employee.ID(), &entity::Employee::ID)) {
        update(employeeData);
    } else {
        create(employeeData);
    }
    return EMPLMGMTSTATUS::SUCCESS;
}

EMPLMGMTSTATUS EmployeeMgmtController::remove(const std::string& employeeID) {
    LOG_DEBUG("Removing employee with ID %s", employeeID.c_str());
    const std::vector<entity::Employee>::iterator it =
                     mCachedList.find(employeeID, &entity::Employee::ID);
    if (it == mCachedList.endOfData()) {
        LOG_ERROR("Employee with ID %s was not found in the cache list", employeeID.c_str());
        mView->showDataNotReadyScreen();
        return EMPLMGMTSTATUS::NOT_FOUND;
    }
    mDataProvider->removeWithID(employeeID);
    /*!
     * Todo (code) - check if mDataProvider successfully removed the employee
     * E.g. failure: mDataprovider lost db connection
    */
    // Remove from cache
    mCachedList.erase(it);
    mView->showSuccessfullyRemoved(employeeID);
    LOG_INFO("Successfully removed employee with ID %s", employeeID.c_str());
    return EMPLMGMTSTATUS::SUCCESS;
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

ValidationErrors EmployeeMgmtController::validateDetails(const entity::Employee& employee) const {
    ValidationErrors validationErrors;
     // validate key employee data
    {
        entity::validator::EmployeeValidator validator(employee);
        validationErrors.merge(validator.result());
    }
    // validate basic information
    {
        entity::validator::PersonValidator validator(employee);
        validationErrors.merge(validator.result());
    }
    // validate address
    {
        entity::validator::AddressValidator validator(employee.address());
        validationErrors.merge(validator.result());
    }
    // validate contact information
    {
        entity::validator::ContactDetailsValidator validator(employee.contactDetails());
        validationErrors.merge(validator.result());
    }
    // validate ID
    {
        for (const entity::PersonalId& personalId : employee.personalIds()) {
            entity::validator::PersonalIDValidator validator(personalId);
            validationErrors.merge(validator.result());
        }
    }
    return validationErrors;
}

EmpMgmtControllerPtr createEmployeeMgmtModule(const EmpMgmtDataPtr& data,
                                              const EmpMgmtViewPtr& view) {
    return std::make_unique<EmployeeMgmtController>(data, view);
}

}  // namespace empmgmt
}  // namespace domain
