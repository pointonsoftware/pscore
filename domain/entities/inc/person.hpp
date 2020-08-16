/**************************************************************************//**
*         Copyright (C) Pointon Software - All Rights Reserved                *
*                                                                             *
*   Unauthorized copying of this file via any medium is strictly prohibited   *
*   Proprietary and confidential                                              *
*                                                                             *
*   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020               *
*                                                                             *
******************************************************************************/
#ifndef DOMAIN_ENTITIES_PERSON
#define DOMAIN_ENTITIES_PERSON

#include <string>
#include <vector>
#include "address.hpp"
#include "personalid.hpp"

namespace domain {
namespace entities {

class Person {
 public:
    Person(const std::string& firstname,
           const std::string& middlename,
           const std::string& lastname, 
           const std::string& birthdate,
           const std::string& gender);
    Person() = default;
    virtual ~Person() = default;

    void addPhoneNumber(const std::string& phonenumber);
    void addEmail(const std::string& email);
    void setPhoneNumbers(const std::vector<std::string>& phonenumbers);
    void setEmails(const std::vector<std::string>& emails);
    void setAddress(const Address& address);
    
 private:
    std::string m_firstname;
    std::string m_middlename;
    std::string m_lastname;
    std::string m_birthdate;
    std::string m_gender;
    std::vector<std::string> m_phone_numbers;
    std::vector<std::string> m_emails;
    std::vector<PersonalId> m_personalIds;
    Address m_address;
};

}  // entities
}  // domain

#endif