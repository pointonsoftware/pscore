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
#include "employeedata.hpp"
#include <algorithm>
#include <string>
#include <vector>
#include <storage/stackdb.hpp>

namespace dataprovider {
namespace empmgmt {

std::vector<entity::Employee> EmployeeDataProvider::getEmployees() {
    return DATABASE().getEmployeesList();
}

void EmployeeDataProvider::removeWithID(const std::string& id) {
    std::vector<entity::Employee>& employeeList = DATABASE().getEmployeesList();
    employeeList.erase(
        std::remove_if(employeeList.begin(), employeeList.end(), [&](const entity::Employee& e) {
            return e.employeeID() == id;
        }), employeeList.end());
}

}  // namespace empmgmt
}  // namespace dataprovider

