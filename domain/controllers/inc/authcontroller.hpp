/**************************************************************************//**
*         Copyright (C) Pointon Software - All Rights Reserved                *
*                                                                             *
*   Unauthorized copying of this file via any medium is strictly prohibited   *
*   Proprietary and confidential                                              *
*                                                                             *
*   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020               *
*                                                                             *
******************************************************************************/
#ifndef DOMAIN_CONTROLLERS_AUTHENTICATION
#define DOMAIN_CONTROLLERS_AUTHENTICATION

#include <authviewif.hpp>
#include <authdataif.hpp>
#include <defines.hpp>
#include <string>
#include <memory>

namespace domain {
namespace controllers {

class AuthController {
 public:
    explicit AuthController(std::unique_ptr<AuthViewIface>&& view, 
                     std::unique_ptr<AuthDataProviderIface>&& dataprovider);
    bool login(const std::string& pin);
 private:
    status::General authenticate(const std::string& pin);
    std::unique_ptr<AuthViewIface> mView;
    std::unique_ptr<AuthDataProviderIface> mDataProvider;
};

}  // controllers
}  // domain

#endif