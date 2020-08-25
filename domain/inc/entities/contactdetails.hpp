/**************************************************************************************************
*                      Copyright (C) Pointon Software - All Rights Reserved                       *
*                                                                                                 *
*             Unauthorized copying of this file via any medium is strictly prohibited             *
*                                  Proprietary and confidential                                   *
*                                                                                                 *
*                   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020                   *
*                                                                                                 *
**************************************************************************************************/
#ifndef DOMAIN_INC_ENTITIES_CONTACTDETAILS_HPP_
#define DOMAIN_INC_ENTITIES_CONTACTDETAILS_HPP_

#include <string>
#include <vector>

namespace domain {
namespace entities {

struct ContactDetails {
    std::string name;
    std::string email;
    std::vector<std::string> phone_number;
};

}  // namespace entities
}  // namespace domain
#endif  // DOMAIN_INC_ENTITIES_CONTACTDETAILS_HPP_