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
#include <algorithm>

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

std::string Person::getFullName() const {
    // Todo (code). There might be a fancier way than this
    return m_firstname + " " + m_middlename + " " + m_lastname;
}

std::string Person::firstName() const {
    return m_firstname;
}

std::string Person::middleName() const {
    return m_middlename;
}

std::string Person::lastName() const {
    return m_lastname;
}

std::string Person::birthdate() const {
    return m_birthdate;
}

std::string Person::gender() const {
    return m_gender;
}

Address Person::address() const {
    return m_address;
}

ContactDetails Person::contactDetails() const {
    return m_contact_details;
}

std::vector<PersonalId> Person::personalIds() const {
    return m_personal_ids;
}

void Person::setFirstName(const std::string& fname) {
    m_firstname = fname;
}

void Person::setMiddleName(const std::string& mname) {
    m_middlename = mname;
}

void Person::setLastName(const std::string& lname) {
    m_lastname = lname;
}

void Person::setBirthdate(const std::string& bdate) {
    m_birthdate = bdate;
}

void Person::setGender(const std::string& gender) {
    m_gender = gender;
}

void Person::setPhoneNumbers(const std::string& phone_1, const std::string& phone_2) {
    m_contact_details.phone_number_1 = phone_1;
    m_contact_details.phone_number_2 = phone_2;
}

void Person::addPersonalId(const std::string& type, const std::string& number) {
    m_personal_ids.emplace_back(PersonalId{type, number});
}

void Person::deletePersonalId(const uint8_t& index) {
    if(index < m_personal_ids.size()) {
        m_personal_ids.erase(m_personal_ids.begin() + index);
    }
}

void Person::setEmail(const std::string& email) {
    m_contact_details.email = email;
}

void Person::setAddress(const Address& address) {
    m_address = address;
}

}  // namespace entity