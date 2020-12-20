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
#include "employee.hpp"
#include <chrono>
#include <ctime>
#include <random>
#include <string>

namespace entity {

Employee::Employee(const std::string& employeeID,
                   const std::string& firstname,
                   const std::string& middlename,
                   const std::string& lastname,
                   const std::string& birthdate,
                   const std::string& gender,
                   const std::string& position,
                   const std::string& status,
                   const bool isSystemUser)
: Person{firstname, middlename, lastname, birthdate, gender},
  mEmployeeID(employeeID), mPosition(position), mStatus(status), mIsSystemUser(isSystemUser) {
    // Empty for now
}

Employee::Employee(const std::string& employeeID) : mEmployeeID(employeeID) {
    // Empty for now
}

}  // namespace entity
