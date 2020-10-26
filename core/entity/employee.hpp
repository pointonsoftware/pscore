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
#ifndef CORE_ENTITY_EMPLOYEE_HPP_
#define CORE_ENTITY_EMPLOYEE_HPP_

#include <string>
#include "person.hpp"

namespace entity {

class Employee : public Person {
 public:
    Employee(const std::string& firstname,
             const std::string& middlename,
             const std::string& lastname,
             const std::string& birthdate,
             const std::string& gender,
             const std::string& employeeID,
             const std::string& position,
             const bool isSystemUser = false);
    Employee() = default;
    ~Employee() = default;

    inline const std::string employeeID() const {
        return mEmployeeID;
    }

    inline const std::string position() const {
        return mPosition;
    }

    inline const bool isSystemUser() const {
        return mIsSystemUser;
    }

    /*!
     * Generate employee ID
     * Note: this should only be used when creating a new employee/user
    */
    std::string generateID() const;

 protected:
    std::string mEmployeeID;
    std::string mPosition;
    bool mIsSystemUser;

    int makeUniqueNumber() const;
    std::string getDate() const;
};

}  // namespace entity
#endif  // CORE_ENTITY_EMPLOYEE_HPP_
