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
#ifndef CORE_DOMAIN_USERLOGIN_LOGINCONTROLLER_HPP_
#define CORE_DOMAIN_USERLOGIN_LOGINCONTROLLER_HPP_

#include <memory>
#include <string>
#include "interface/loginiface.hpp"
#include "interface/logindataif.hpp"
#include "interface/loginviewif.hpp"

// Entity
#include <entity/user.hpp>

namespace domain {
namespace login {

enum class AUTHSTATUS {
    SUCCESS       = 0,
    FAILED        = 1,
    UNINITIALIZED = 2
};

class LoginController : public LoginControlInterface {
 public:
    explicit LoginController(const std::shared_ptr<LoginDataProviderIface>& dataprovider,
                            const std::shared_ptr<LoginViewIface>& view);
    bool authenticate(const std::string& id, const std::string& pin) override;
 private:
    std::shared_ptr<LoginDataProviderIface> mDataProvider;
    std::shared_ptr<LoginViewIface> mView;
    AUTHSTATUS getUserByPIN(const std::string& pin, entity::User* user);
    bool isPinValid(const std::string& pin) const;
    bool isUserValid(const entity::User& userInfo) const;
};

}  // namespace login
}  // namespace domain
#endif  // CORE_DOMAIN_USERLOGIN_LOGINCONTROLLER_HPP_