/**************************************************************************************************
*                      Copyright (C) Pointon Software - All Rights Reserved                       *
*                                                                                                 *
*             Unauthorized copying of this file via any medium is strictly prohibited             *
*                                  Proprietary and confidential                                   *
*                                                                                                 *
*                   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020                   *
*                                                                                                 *
**************************************************************************************************/
#ifndef DOMAIN_ENTITIES_INC_PERSONALID_HPP_
#define DOMAIN_ENTITIES_INC_PERSONALID_HPP_

#include <string>

namespace domain {
namespace entities {

struct PersonalId {
    std::string type;
    std::string id_number;
};

}  // namespace entities
}  // namespace domain
#endif  // DOMAIN_ENTITIES_INC_PERSONALID_HPP_