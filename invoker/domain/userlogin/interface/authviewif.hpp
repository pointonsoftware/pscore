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
#ifndef INVOKER_DOMAIN_USERLOGIN_INTERFACE_AUTHVIEWIF_HPP_
#define INVOKER_DOMAIN_USERLOGIN_INTERFACE_AUTHVIEWIF_HPP_
#include <string>
// Entity
#include <entity/user.hpp>

namespace domain {
namespace authentication {

class AuthViewIface {
 public:
    AuthViewIface() = default;
    virtual ~AuthViewIface() = default;

    /**
    * Will be called if user was found
    */
    virtual void loginSuccessful(const entity::User& userInfo) = 0;

    /**
    * invalid PIN!
    */
    virtual void showInvalidPINScreen() = 0;

    /**
    * user not found
    */
    virtual void showUserNotFoundScreen() = 0;

    /**
    * will be called if something went wrong with the database
    */
    virtual void showDataNotReadyScreen() = 0;
};

}  // namespace authentication
}  // namespace domain
#endif  // INVOKER_DOMAIN_USERLOGIN_INTERFACE_AUTHVIEWIF_HPP_