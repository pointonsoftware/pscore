/**************************************************************************************************
*                      Copyright (C) Pointon Software - All Rights Reserved                       *
*                                                                                                 *
*             Unauthorized copying of this file via any medium is strictly prohibited             *
*                                  Proprietary and confidential                                   *
*                                                                                                 *
*                   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020                   *
*                                                                                                 *
**************************************************************************************************/
#include <entities/employee.hpp>

namespace domain {
namespace entities {

Employee::Employee(const std::string& firstname,
                   const std::string& middlename,
                   const std::string& lastname,
                   const std::string& birthdate,
                   const std::string& gender)
: Person{firstname, middlename, lastname, birthdate, gender} {
    // Empty for now
}

}  // namespace entities
}  // namespace domain
