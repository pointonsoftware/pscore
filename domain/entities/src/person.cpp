/**************************************************************************//**
*         Copyright (C) Pointon Software - All Rights Reserved                *
*                                                                             *
*   Unauthorized copying of this file via any medium is strictly prohibited   *
*   Proprietary and confidential                                              *
*                                                                             *
*   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020               *
*                                                                             *
******************************************************************************/
#include <inc/person.hpp>

namespace domain {
namespace entities {

Person::Person(const std::string& firstname, 
               const std::string& middlename,
               const std::string& lastname,
               const std::string& birthdate,
               const std::string& gender) 
: m_firstname(firstname), m_middlename(middlename), m_lastname(lastname),
  m_birthdate(birthdate), m_gender(gender) {
    // Empty for now
}

void Person::addPhoneNumber(const std::string& phonenumber) {
    m_contact_details.phone_number.emplace_back(phonenumber);
}

void Person::addPersonalId(const std::string& type, const std::string& number) {
    m_personal_ids.emplace_back(PersonalId{type, number});
}

void Person::setPersonalIds(const std::vector<PersonalId>& personalids) {
    if(!m_personal_ids.empty()) {
        // warning, we're overwriting the container
    }
    m_personal_ids = personalids;
}

void Person::setEmail(const std::string& email) {
    m_contact_details.email = email;
}

void Person::setAddress(const Address& address) {
    m_address = address;
}

}  // entities
}  // domain