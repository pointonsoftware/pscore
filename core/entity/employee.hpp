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

// Fields
constexpr char FIELD_EMPID[] = "Employee.ID";
constexpr char FIELD_EPOS[] = "Employee.Position";
constexpr char FIELD_ESTATUS[] = "Employee.Status";

class Employee : public Person {
 public:
    Employee(const std::string& id,
             const std::string& firstname,
             const std::string& middlename,
             const std::string& lastname,
             const std::string& birthdate,
             const std::string& gender,
             const std::string& position,
             const std::string& status,
             const bool isSystemUser);
    explicit Employee(const std::string& id);
    Employee() = default;
    ~Employee() = default;

    inline std::string ID() const {
        return mID;
    }

    inline void setPosition(const std::string& position) {
        mPosition = position;
    }

    inline std::string position() const {
        return mPosition;
    }

    inline void setIsSystemUser(const bool isUser) {
        mIsSystemUser = isUser;
    }

    inline bool isSystemUser() const {
        return mIsSystemUser;
    }

    inline void setStatus(const std::string& status) {
        mStatus = status;
    }

    inline std::string status() const {
        return mStatus;
    }

 protected:
    std::string mID;
    std::string mPosition;
    std::string mStatus;
    bool mIsSystemUser = false;

    // Todo (spec) - add employee photo
};

}  // namespace entity
#endif  // CORE_ENTITY_EMPLOYEE_HPP_
