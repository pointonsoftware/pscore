/**************************************************************************************************
*                      Copyright (C) Pointon Software - All Rights Reserved                       *
*                                                                                                 *
*             Unauthorized copying of this file via any medium is strictly prohibited             *
*                                  Proprietary and confidential                                   *
*                                                                                                 *
*                   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020                   *
*                                                                                                 *
**************************************************************************************************/
#ifndef DOMAIN_PUBLIC_DATAPROVIDER_AUTHDATAIF_HPP_
#define DOMAIN_PUBLIC_DATAPROVIDER_AUTHDATAIF_HPP_

#include "dataproviderif.hpp"

namespace domain {
namespace authentication {

class AuthDataProviderIface : public DataProviderIface {
 public:
    AuthDataProviderIface() = default;
    virtual ~AuthDataProviderIface() = default;
};

}  // namespace authentication
}  // namespace domain
#endif  // DOMAIN_PUBLIC_DATAPROVIDER_AUTHDATAIF_HPP_