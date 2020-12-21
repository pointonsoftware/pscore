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
#ifndef CORE_ENTITY_USER_HPP_
#define CORE_ENTITY_USER_HPP_

#include <string>
#include "employee.hpp"

namespace entity {

// Fields
constexpr char FIELD_UID[] = "User.ID";
constexpr char FIELD_ROLE[] = "User.Role";
constexpr char FIELD_PIN[] = "User.Pin";
constexpr char FIELD_CDATE[] = "User.CreatedAt";

class User {
 public:
    User(const std::string& userID,
         const std::string& role,
         const std::string& pin,
         const std::string& createdAt,
         const std::string& employeeID);

    User() = default;
    ~User() = default;

    // Setters
    void setRole(const std::string& role) {
        mRole = role;
    }
    void setPIN(const std::string& pin) {
        mPIN = pin;
    }
    void setEmployeeID(const std::string& employeeID) {
        mEmployeeID = employeeID;
    }

    // Getters
    inline const std::string userID() const {
        return mUserID;
    }
    inline const std::string role() const {
        return mRole;
    }
    inline const std::string pin() const {
        return mPIN;
    }
    inline const std::string createdAt() const {
        return mCreatedAt;
    }
    inline const std::string employeeID() const {
        return mEmployeeID;
    }

 private:
    std::string mUserID;
    std::string mRole;
    std::string mPIN;
    std::string mCreatedAt;
    std::string mEmployeeID;
};

}  // namespace entity
#endif  // CORE_ENTITY_USER_HPP_
