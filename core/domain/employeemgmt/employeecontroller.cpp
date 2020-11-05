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
#include <logger/loghelper.hpp>

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
    // Make sure view is valid
    if (!mView) {
        LOG_ERROR("View is not initialized");
        return {};
    }
    if (!mDataProvider) {
        LOG_ERROR("Dataprovider is not initialized");
        mView->showDataNotReadyScreen();
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

USERSMGMTSTATUS EmployeeMgmtController::save(const entity::User& userID) {
    // PCOR-32
    // Generate employeeID from Employee entity if employee is new
    return USERSMGMTSTATUS::SUCCESS;
}

USERSMGMTSTATUS EmployeeMgmtController::remove(const std::string& id) {
    LOG_DEBUG("Removing employee with ID %s", id.c_str());
    if (!mView) {
        LOG_ERROR("View is not initialized");
        return USERSMGMTSTATUS::UNINITIALIZED;
    }
    if (!mDataProvider) {
        LOG_ERROR("Dataprovider is not initialized");
        mView->showDataNotReadyScreen();
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

}  // namespace empmgmt
}  // namespace domain
