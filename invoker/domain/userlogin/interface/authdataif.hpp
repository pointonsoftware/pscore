/**************************************************************************************************
*                                            PSCORE                                               *
*                               Copyright (C) 2020 Pointon Software                               *
*                                                                                                 *
*           This program is free software: you can redistribute it and/or modify                  *
*           it under the terms of the GNU Affero General Public License as published              *
*           by the Free Software Foundation, either version 3 of the License, or                  *
*           (at your option) any later version.                                                   *
*                                                                                                 *
*           This program is distributed in the hope that it will be useful,                       *
*           but WITHOUT ANY WARRANTY; without even the implied warranty of                        *
*           MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                         *
*           GNU Affero General Public License for more details.                                   *
*                                                                                                 *
*           You should have received a copy of the GNU Affero General Public License              *
*           along with this program.  If not, see <https://www.gnu.org/licenses/>.                *
*                                                                                                 *
*           Ben Ziv <pointonsoftware@gmail.com>                                                   *
*                                                                                                 *
**************************************************************************************************/
#ifndef INVOKER_DOMAIN_USERLOGIN_INTERFACE_AUTHDATAIF_HPP_
#define INVOKER_DOMAIN_USERLOGIN_INTERFACE_AUTHDATAIF_HPP_
#include <entity/user.hpp>

namespace domain {
namespace authentication {

class AuthDataProviderIface {
 public:
    AuthDataProviderIface() = default;
    virtual ~AuthDataProviderIface() = default;

    /*!
     * entity::User findUserByPin(const std::string& pin)
     * Finds a user that's assigned with the pin argument
     * Will return user->pin = 0 if user is not found.
     *
     * [in] input pin
     * [return] user class
    */
    virtual entity::User findUserByPin(const std::string& inputPin) = 0;
};

}  // namespace authentication
}  // namespace domain
#endif  // INVOKER_DOMAIN_USERLOGIN_INTERFACE_AUTHDATAIF_HPP_