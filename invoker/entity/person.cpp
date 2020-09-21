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
#include "person.hpp"

namespace entity {

Person::Person(const std::string& firstname,
               const std::string& middlename,
               const std::string& lastname,
               const std::string& birthdate,
               const std::string& gender)
: m_firstname(firstname), m_middlename(middlename), m_lastname(lastname),
  m_birthdate(birthdate), m_gender(gender) {
    // Empty for now
}
// cppcheck-suppress unusedFunction
void Person::addPhoneNumber(const std::string& phonenumber) {
    m_contact_details.phone_number.emplace_back(phonenumber);
}
// cppcheck-suppress unusedFunction
void Person::addPersonalId(const std::string& type, const std::string& number) {
    m_personal_ids.emplace_back(PersonalId{type, number});
}
// cppcheck-suppress unusedFunction
void Person::setPersonalIds(const std::vector<PersonalId>& personalids) {
    if (!m_personal_ids.empty()) {
        // warning, we're overwriting the container
    }
    m_personal_ids = personalids;
}
// cppcheck-suppress unusedFunction
void Person::setEmail(const std::string& email) {
    m_contact_details.email = email;
}
// cppcheck-suppress unusedFunction
void Person::setAddress(const Address& address) {
    m_address = address;
}

}  // namespace entity