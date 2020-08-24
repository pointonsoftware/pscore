/**************************************************************************************************
*                      Copyright (C) Pointon Software - All Rights Reserved                       *
*                                                                                                 *
*             Unauthorized copying of this file via any medium is strictly prohibited             *
*                                  Proprietary and confidential                                   *
*                                                                                                 *
*                   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020                   *
*                                                                                                 *
**************************************************************************************************/
#ifndef DOMAIN_PUBLIC_CONTROLLERS_AUTHCONTROLLER_HPP_
#define DOMAIN_PUBLIC_CONTROLLERS_AUTHCONTROLLER_HPP_

#include <string>
#include <memory>
#include <defines.hpp>
#include <views/authviewif.hpp>
#include <dataproviders/authdataif.hpp>

namespace domain {
namespace authentication {

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

}  // namespace authentication
}  // namespace domain
#endif  // DOMAIN_PUBLIC_CONTROLLERS_AUTHCONTROLLER_HPP_