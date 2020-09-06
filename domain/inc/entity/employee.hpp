/**************************************************************************************************
*                      Copyright (C) Pointon Software - All Rights Reserved                       *
*                                                                                                 *
*             Unauthorized copying of this file via any medium is strictly prohibited             *
*                                  Proprietary and confidential                                   *
*                                                                                                 *
*                   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020                   *
*                                                                                                 *
**************************************************************************************************/
#ifndef DOMAIN_INC_ENTITIES_EMPLOYEE_HPP_
#define DOMAIN_INC_ENTITIES_EMPLOYEE_HPP_

#include <string>
#include "person.hpp"

namespace domain {
namespace entities {

class Employee : public Person {
 public:
    Employee(const std::string& firstname,
             const std::string& middlename,
             const std::string& lastname,
             const std::string& birthdate,
             const std::string& gender);
    Employee() = default;
    ~Employee() = default;
 private:
    bool is_system_user;
    std::string position;
};

}  // namespace entities
}  // namespace domain
#endif  // DOMAIN_INC_ENTITIES_EMPLOYEE_HPP_