/**************************************************************************************************
*                      Copyright (C) Pointon Software - All Rights Reserved                       *
*                                                                                                 *
*             Unauthorized copying of this file via any medium is strictly prohibited             *
*                                  Proprietary and confidential                                   *
*                                                                                                 *
*                   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020                   *
*                                                                                                 *
**************************************************************************************************/
#ifndef DOMAIN_PUBLIC_DATAPROVIDER_DATAPROVIDERIF_HPP_
#define DOMAIN_PUBLIC_DATAPROVIDER_DATAPROVIDERIF_HPP_

namespace domain {

class DataProviderIface {
 public:
    DataProviderIface() = default;
    virtual ~DataProviderIface() = default;

    virtual bool getDatabaseStatus() = 0;
};

}  // namespace domain

#endif  // DOMAIN_PUBLIC_DATAPROVIDER_DATAPROVIDERIF_HPP_