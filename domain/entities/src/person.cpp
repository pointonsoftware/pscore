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
    m_phone_numbers.emplace_back(phonenumber);
}

void Person::addEmail(const std::string& email) {
    m_emails.emplace_back(email);
}

void Person::setPhoneNumbers(const std::vector<std::string>& phonenumbers) {
    if(!m_phone_numbers.empty()) {
        // warning, we're overwriting the container
    }
    m_phone_numbers = phonenumbers;
}

void Person::setEmails(const std::vector<std::string>& emails) {
    if(!m_emails.empty()) {
        // warning, we're overwriting the container
    }
    m_emails = emails;
}

void Person::setAddress(const Address& address) {
    m_address = address;
}

}  // entities
}  // domain