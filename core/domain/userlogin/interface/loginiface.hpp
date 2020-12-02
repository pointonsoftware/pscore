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
#ifndef CORE_DOMAIN_USERLOGIN_INTERFACE_LOGINIFACE_HPP_
#define CORE_DOMAIN_USERLOGIN_INTERFACE_LOGINIFACE_HPP_
#include <memory>
#include <string>
#include <domain/librarycommon.hpp>
#include "logindataif.hpp"
#include "loginviewif.hpp"

namespace domain {
namespace login {

class LoginControlInterface {
 public:
    LoginControlInterface() = default;
    virtual ~LoginControlInterface() = default;
    /*!
     * Login with PIN
     * Returns the userID if successful; otherwise, will return empty
    */
    virtual std::string loginWithPIN(const std::string& pin) = 0;
};

// Lib APIs
extern "C" CORE_API std::unique_ptr<LoginControlInterface> createLoginModule(
    const std::shared_ptr<LoginDataProviderIface>& dataprovider,
    const std::shared_ptr<LoginViewIface>& view);

}  // namespace login
}  // namespace domain
#endif  // CORE_DOMAIN_USERLOGIN_INTERFACE_LOGINIFACE_HPP_