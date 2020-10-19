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
    const std::vector<entity::Employee>& temp = mDataProvider->getEmployees();
    if (temp.empty()) {
        LOG_WARN("Employees list is empty");
        mView->showEmployeesEmptyPopup();
        return {};
    }
    LOG_INFO("Successfully retrieved employees list. Size: %d", temp.size());
    return temp;
}

entity::User EmployeeMgmtController::get(const std::string& userID) {
    // PCOR-36
    return entity::User();
}

USERSMGMTSTATUS EmployeeMgmtController::save(const entity::User& userID) {
    // PCOR-32
    return USERSMGMTSTATUS::SUCCESS;
}

USERSMGMTSTATUS EmployeeMgmtController::remove(const std::string& userID) {
    // PCOR-33
    return USERSMGMTSTATUS::SUCCESS;
}

std::unique_ptr<EmployeeMgmtControlInterface> createEmployeeMgmtModule(
                    const std::shared_ptr<EmployeeMgmtDataInterface>& data,
                    const std::shared_ptr<EmployeeMgmtViewInterface>& view) {
    return std::make_unique<EmployeeMgmtController>(data, view);
}

}  // namespace empmgmt
}  // namespace domain
