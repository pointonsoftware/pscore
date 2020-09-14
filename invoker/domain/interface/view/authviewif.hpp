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
#ifndef DOMAIN_PUBLIC_VIEW_AUTHVIEWIF_HPP_
#define DOMAIN_PUBLIC_VIEW_AUTHVIEWIF_HPP_
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
#endif  // DOMAIN_PUBLIC_VIEW_AUTHVIEWIF_HPP_