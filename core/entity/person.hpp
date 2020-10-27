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
#ifndef CORE_ENTITY_PERSON_HPP_
#define CORE_ENTITY_PERSON_HPP_

#include <string>
#include <vector>
#include "address.hpp"
#include "contactdetails.hpp"
#include "personalid.hpp"

namespace entity {

class Person {
 public:
    Person(const std::string& firstname,
           const std::string& middlename,
           const std::string& lastname,
           const std::string& birthdate,
           const std::string& gender);
    Person() = default;
    virtual ~Person() = default;

    // Getters
    std::string getFullName() const;
    std::string firstName() const;
    std::string middleName() const;
    std::string lastName() const;
    std::string birthdate() const;
    std::string gender() const;
    Address address() const;
    ContactDetails contactDetails() const;
    std::vector<PersonalId> personalIds() const;

    // Setters
    Person& addPhoneNumber(const std::string& phonenumber);
    Person& addPersonalId(const std::string& type, const std::string& number);
    Person& setPersonalIds(const std::vector<PersonalId>& personalids);
    Person& setEmail(const std::string& email);
    Person& setAddress(const Address& address);

 protected:
    std::string m_firstname;
    std::string m_middlename;
    std::string m_lastname;
    std::string m_birthdate;
    std::string m_gender;
    Address m_address;
    ContactDetails m_contact_details;
    std::vector<PersonalId> m_personal_ids;
};

}  // namespace entity
#endif  // CORE_ENTITY_PERSON_HPP_