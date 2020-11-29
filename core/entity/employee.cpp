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

Employee::Employee(const std::string& firstname,
                   const std::string& middlename,
                   const std::string& lastname,
                   const std::string& birthdate,
                   const std::string& gender,
                   const std::string& employeeID,
                   const std::string& position,
                   const Status status,
                   const bool isSystemUser)
: Person{firstname, middlename, lastname, birthdate, gender},
  mEmployeeID(employeeID), mPosition(position), mStatus(status), mIsSystemUser(isSystemUser) {
    // Empty for now
}

bool Employee::generateID() {
    if (!mEmployeeID.empty()) {
        return false;
    }
    // Substring the last two digit of the year + unique_number
    mEmployeeID = getDate().substr(2, 2) + std::to_string(makeUniqueNumber());
    return true;
}

std::string Employee::getDate() const {
    typedef std::chrono::system_clock Clock;
    auto now = Clock::now();
    std::time_t now_c = Clock::to_time_t(now);
    struct tm *parts = std::localtime(&now_c);
    char buff[100];
    snprintf(buff, sizeof(buff), "%04u-%02u-%02u", parts->tm_year + 1900,
                  parts->tm_mon + 1, parts->tm_mday);
    return std::string(buff);
}

int Employee::makeUniqueNumber() const {
    std::random_device dev;
    std::mt19937 rng(dev());
    // distribution in range [10000, 99999]
    std::uniform_int_distribution<std::mt19937::result_type> dist6(10000, 99999);
    return dist6(rng);
}

}  // namespace entity
