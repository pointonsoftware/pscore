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
#ifndef DOMAIN_USERLOGIN_AUTHCONTROLLER_HPP_
#define DOMAIN_USERLOGIN_AUTHCONTROLLER_HPP_

#include <memory>
#include <string>
#include "interface/logincontrolif.hpp"
#include "interface/logindataif.hpp"
#include "interface/loginviewif.hpp"

// Entity
#include <entity/user.hpp>

namespace domain {
namespace login {

class LoginController {
 public:
    explicit LoginController(const std::shared_ptr<LoginDataProviderIface>& dataprovider,
                            const std::shared_ptr<LoginViewIface>& view);
    bool login(const std::string& username, const std::string& password);
    bool loginWithPIN(const std::string& pin);
 private:
    std::shared_ptr<LoginDataProviderIface> mDataProvider;
    std::shared_ptr<LoginViewIface> mView;
    AUTHSTATUS getUserByPIN(const std::string& pin, entity::User* user);
    bool isPinValid(const std::string& pin) const;
    bool isUserValid(const entity::User& userInfo) const;
};

}  // namespace login
}  // namespace domain
#endif  // DOMAIN_USERLOGIN_AUTHCONTROLLER_HPP_