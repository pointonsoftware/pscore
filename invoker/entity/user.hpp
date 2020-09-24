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
#ifndef INVOKER_ENTITY_USER_HPP_
#define INVOKER_ENTITY_USER_HPP_

#include <string>
#include "employee.hpp"

namespace entity {

class User : public Employee {
 public:
    User(const std::string& firstname,
             const std::string& middlename,
             const std::string& lastname,
             const std::string& birthdate,
             const std::string& gender,
             const std::string& pin = DEFAULT_PIN);
    User();
    ~User() = default;

    // Sorry to make this public :/
    // But its const anyway
    static constexpr unsigned int PIN_SIZE = 4;
    static constexpr char DEFAULT_PIN[PIN_SIZE + 1] = "0000";
    inline const std::string pin() const {
        return mPIN;
    }

 private:
    std::string mPIN;
};

}  // namespace entity
#endif  // INVOKER_ENTITY_USER_HPP_
