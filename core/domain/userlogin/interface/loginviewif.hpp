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
#ifndef CORE_DOMAIN_USERLOGIN_INTERFACE_LOGINVIEWIF_HPP_
#define CORE_DOMAIN_USERLOGIN_INTERFACE_LOGINVIEWIF_HPP_
#include <string>
#include <entity/user.hpp>

namespace domain {
namespace login {

class LoginViewIface {
 public:
    LoginViewIface() = default;
    virtual ~LoginViewIface() = default;

    /**
     * User not found
     */
    virtual void showUserNotFoundScreen() = 0;

    /**
     * Will be called if something went wrong with the database
     */
    virtual void showDataNotReadyScreen() = 0;
};

}  // namespace login
}  // namespace domain
#endif  // CORE_DOMAIN_USERLOGIN_INTERFACE_LOGINVIEWIF_HPP_
