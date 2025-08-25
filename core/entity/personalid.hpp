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
#ifndef CORE_ENTITY_PERSONALID_HPP_
#define CORE_ENTITY_PERSONALID_HPP_

#include <string>

namespace entity {

// Fields
constexpr char FIELD_PNID_IDT[] = "PersonalId.Type";
constexpr char FIELD_PNID_IDN[] = "PersonalId.Number";

struct PersonalId {
 public:
    PersonalId(const std::string& email, const std::string& phone1)
                   : mType(email), mIdNumber(phone1) {}
    PersonalId() = default;
    ~PersonalId() = default;
     // Setters
    void setType(const std::string& str) {
        mType = str;
    }
    void setNumber(const std::string& str) {
        mIdNumber = str;
    }
    // Getters
    const std::string& type() const {
        return mType;
    }
    const std::string& number() const {
        return mIdNumber;
    }

 private:
    std::string mType;
    std::string mIdNumber;
};

}  // namespace entity
#endif  // CORE_ENTITY_PERSONALID_HPP_