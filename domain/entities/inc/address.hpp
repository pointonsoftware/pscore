/**************************************************************************//**
*         Copyright (C) Pointon Software - All Rights Reserved                *
*                                                                             *
*   Unauthorized copying of this file via any medium is strictly prohibited   *
*   Proprietary and confidential                                              *
*                                                                             *
*   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020               *
*                                                                             *
******************************************************************************/
#ifndef DOMAIN_ENTITIES_ADDRESS
#define DOMAIN_ENTITIES_ADDRESS

#include <string>

namespace domain {
namespace entities {

struct Address {
    std::string sitio;
    std::string purok;
    std::string barangay;
    std::string town;
    std::string province;
    std::string zip;
};

}  // entities
}  // domain

#endif