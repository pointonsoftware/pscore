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
#include <string>

namespace domain {
namespace authentication {

class AuthViewIface {
 public:
    AuthViewIface() = default;
    virtual ~AuthViewIface() = default;

    /**
    * showLoginScreen
    */
    virtual void showLoginScreen() = 0;

    /**
    * showLoginFailed
    */
    virtual void showLoginFailed() = 0;
    
    /**
    * Will be called if user was found
    * @param employee a JSON string containing employee details
    */
    virtual void loginSuccessful(const std::string& employee) = 0;
};

}  // namespace authentication
}  // namespace domain
#endif  // DOMAIN_PUBLIC_AUTHVIEWIF_HPP_