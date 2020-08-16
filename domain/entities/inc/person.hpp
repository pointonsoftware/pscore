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
#include "contactdetails.hpp"
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
    void addPersonalId(const std::string& type, const std::string& number);
    void setPersonalIds(const std::vector<PersonalId>& personalids);
    void setEmail(const std::string& email);
    void setAddress(const Address& address);
    
 private:
    std::string m_firstname;
    std::string m_middlename;
    std::string m_lastname;
    std::string m_birthdate;
    std::string m_gender;
    std::string m_email;
    Address m_address;
    ContactDetails m_contact_details;
    std::vector<PersonalId> m_personal_ids;
};

}  // entities
}  // domain

#endif