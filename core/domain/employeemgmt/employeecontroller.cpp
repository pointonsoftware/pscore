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
#include <logger/loghelper.hpp>
#include <validator/addressvalidator.hpp>
#include <validator/contactdetailsvalidator.hpp>
#include <validator/personalidvalidator.hpp>
#include <validator/personvalidator.hpp>
#include <validator/uservalidator.hpp>

namespace domain {
namespace empmgmt {

EmployeeMgmtController::EmployeeMgmtController(
                                    const std::shared_ptr<EmployeeMgmtDataInterface>& data,
                                    const std::shared_ptr<EmployeeMgmtViewInterface>& view)
: mDataProvider(data), mView(view) {
    // empty for now
}

std::vector<entity::Employee> EmployeeMgmtController::list() {
    LOG_DEBUG("Getting the list of employees");
    if (!isInterfaceInitialized()) {
        return {};
    }
    mCachedList = mDataProvider->getEmployees();
    if (mCachedList.empty()) {
        LOG_WARN("Employees list is empty");
        mView->showEmployeesEmptyPopup();
        return {};
    }
    LOG_INFO("Successfully retrieved employees list. Size: %d", mCachedList.size());
    return mCachedList;
}

entity::Employee EmployeeMgmtController::get(const std::string& id) {
    LOG_DEBUG("Getting employee with ID %s", id.c_str());
    const std::vector<entity::Employee>::iterator& iter = find(id);
    if (iter != mCachedList.end()) {
        LOG_INFO("Found employee with ID %s", id.c_str());
        return *iter;
    } else {
        LOG_ERROR("Employee was not found");
        return entity::Employee{};
    }
}

USERSMGMTSTATUS EmployeeMgmtController::save(const SaveEmployeeData& employeeData) {
    const entity::Employee& employee = employeeData.employee;
    std::map<std::string, std::string>* validationResult = employeeData.validationResult;
    LOG_DEBUG("Saving employee information");
    if (!isInterfaceInitialized()) {
        return USERSMGMTSTATUS::UNINITIALIZED;
    }
    if (!validationResult) {
        LOG_ERROR("Validation-message container is not initialized");
        mView->showDataNotReadyScreen();
        return USERSMGMTSTATUS::UNINITIALIZED;
    }
    // Fill the validation results
    *(validationResult) = validateDetails(employee);
    // Todo (code) - uncomment when user entity is updated
    // if (employee.isSystemUser()) {
        // Validate User
        // entity::validator::UserValidator validator(employeeData.PIN);
        // validationErrors->insert(validator.result().begin(), validator.result().end());
    // }
    if (!validationResult->empty()) {
        LOG_WARN("Entity contains invalid data. Returning validation results.");
        dumpValidationResult(*(validationResult));
        return USERSMGMTSTATUS::FAILED;
    }
    if (!employee.employeeID().empty()) {
        LOG_DEBUG("EmployeeID is not empty");
        if (isExists(employee.employeeID())) {
            // Todo (code) - add Update
            LOG_INFO("Employee %s %s updated", employee.firstName().c_str(),
                     employee.lastName().c_str());
            return USERSMGMTSTATUS::SUCCESS;
        }
    }
    // Generate ID for the new employee
    entity::Employee newEmployee = employee;
    newEmployee.generateID();
    LOG_INFO("EmployeeID %s generated", newEmployee.employeeID().c_str());
    mDataProvider->create(newEmployee);
    // Todo (code) - uncomment when user entity is updated
    // if (employee.isSystemUser()) {
        // mDataProvider->Create(User);
    // }
    /*!
     * Todo (code) - add checking if create is successful from dataprovider
     * before updating the cache
    */
    mCachedList.emplace_back(newEmployee);
    LOG_INFO("Employee %s %s added", employee.firstName().c_str(), employee.lastName().c_str());
    return USERSMGMTSTATUS::SUCCESS;
}

USERSMGMTSTATUS EmployeeMgmtController::remove(const std::string& id) {
    LOG_DEBUG("Removing employee with ID %s", id.c_str());
    if (!isInterfaceInitialized()) {
        return USERSMGMTSTATUS::UNINITIALIZED;
    }
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
                return e.employeeID() == id;
            });
}

std::unique_ptr<EmployeeMgmtControlInterface> createEmployeeMgmtModule(
                    const std::shared_ptr<EmployeeMgmtDataInterface>& data,
                    const std::shared_ptr<EmployeeMgmtViewInterface>& view) {
    return std::make_unique<EmployeeMgmtController>(data, view);
}

bool EmployeeMgmtController::isInterfaceInitialized() const {
    if (!mView) {
        LOG_ERROR("View is not initialized");
        return false;
    }
    if (!mDataProvider) {
        LOG_ERROR("Dataprovider is not initialized");
        mView->showDataNotReadyScreen();
        return false;
    }
    return true;
}

ValidationErrors EmployeeMgmtController::validateDetails(const entity::Employee& employee) const {
    ValidationErrors validationErrors;
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
}  // namespace empmgmt
}  // namespace domain
