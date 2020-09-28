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
#ifndef CORE_DOMAIN_USERLOGIN_INTERFACE_LOGINDATAIF_HPP_
#define CORE_DOMAIN_USERLOGIN_INTERFACE_LOGINDATAIF_HPP_
#include <string>
#include <entity/user.hpp>

namespace domain {
namespace login {
/*!
 * Note: If you add/update a function in this interface, please also update the mock class
*/
class LoginDataProviderIface {
 public:
    LoginDataProviderIface() = default;
    virtual ~LoginDataProviderIface() = default;

    /*!
     * entity::User findUserByPin(const std::string& pin)
     * Looks for the user that's assigned with the pin argument
     * Will return user->pin = entity::User::DEFAULT_PIN if user is not found.
     *
     * [in] input pin
     * [return] user class
    */
    virtual entity::User findUserByPin(const std::string& inputPin) = 0;
};

}  // namespace login
}  // namespace domain
#endif  // CORE_DOMAIN_USERLOGIN_INTERFACE_LOGINDATAIF_HPP_
