/**************************************************************************//**
*         Copyright (C) Pointon Software - All Rights Reserved                *
*                                                                             *
*   Unauthorized copying of this file via any medium is strictly prohibited   *
*   Proprietary and confidential                                              *
*                                                                             *
*   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020               *
*                                                                             *
******************************************************************************/
#ifndef DOMAIN_PUBLIC_DATAPROVIDER
#define DOMAIN_PUBLIC_DATAPROVIDER

namespace domain {

class DataProviderIface {
 public:
    DataProviderIface() = default;
    virtual ~DataProviderIface() = default;

    virtual bool getDatabaseStatus() = 0;
};

}  // domain

#endif