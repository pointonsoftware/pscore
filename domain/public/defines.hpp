/**************************************************************************************************
*                      Copyright (C) Pointon Software - All Rights Reserved                       *
*                                                                                                 *
*             Unauthorized copying of this file via any medium is strictly prohibited             *
*                                  Proprietary and confidential                                   *
*                                                                                                 *
*                   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020                   *
*                                                                                                 *
**************************************************************************************************/
#ifndef DOMAIN_PUBLIC_DEFINES_HPP_
#define DOMAIN_PUBLIC_DEFINES_HPP_

namespace domain {
namespace status {

enum class General {
    FAILED   = 0,
    SUCCESS  = 1,
    BUSY     = 2,
    EXISTS   = 3,
    OFFLINE  = 4,
    EMPTY    = 5,
    OCCUPIED = 6,
};

}  // namespace status
}  // namespace domain

#endif  // DOMAIN_PUBLIC_DEFINES_HPP_