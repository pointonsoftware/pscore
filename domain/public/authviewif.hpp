/**************************************************************************************************
*                      Copyright (C) Pointon Software - All Rights Reserved                       *
*                                                                                                 *
*             Unauthorized copying of this file via any medium is strictly prohibited             *
*                                  Proprietary and confidential                                   *
*                                                                                                 *
*                   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020                   *
*                                                                                                 *
**************************************************************************************************/
#ifndef DOMAIN_PUBLIC_AUTHVIEWIF_HPP_
#define DOMAIN_PUBLIC_AUTHVIEWIF_HPP_

#include <inc/employee.hpp>

namespace domain {
namespace authentication {

class AuthViewIface {
 public:
    AuthViewIface() = default;
    virtual ~AuthViewIface() = default;

    virtual void showLoginScreen() = 0;
    virtual void showLoginFailed() = 0;
    virtual void loginSuccessful(const entities::Employee& employee) = 0;
};

}  // namespace authentication
}  // namespace domain
#endif  // DOMAIN_PUBLIC_AUTHVIEWIF_HPP_