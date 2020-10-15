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

EmployeeMgmtController::EmployeeMgmtController() {
    // empty for now
}

std::vector<entity::User> EmployeeMgmtController::list() {
    // PCOR-34
    return {};
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

std::unique_ptr<EmployeeMgmtControlInterface> createUsersMgmtModule() {
    return std::make_unique<EmployeeMgmtController>();
}

}  // namespace empmgmt
}  // namespace domain
