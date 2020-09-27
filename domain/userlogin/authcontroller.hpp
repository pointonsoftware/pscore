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
#include <defines.hpp>
#include "interface/authviewif.hpp"
#include "interface/authdataif.hpp"
// Entity
#include <entity/user.hpp>

namespace domain {
namespace authentication {

class AuthController {
 public:
    explicit AuthController(const std::shared_ptr<AuthDataProviderIface>& dataprovider,
                            const std::shared_ptr<AuthViewIface>& view);
    bool login(const std::string& username, const std::string& password);
    bool loginWithPIN(const std::string& pin);
 private:
    std::shared_ptr<AuthViewIface> mView;
    std::shared_ptr<AuthDataProviderIface> mDataProvider;
    status::General getUserByPIN(const std::string& pin, entity::User* user);
    bool isPinValid(const std::string& pin) const;
    bool isUserValid(const entity::User& userInfo) const;
};

}  // namespace authentication
}  // namespace domain
#endif  // DOMAIN_USERLOGIN_AUTHCONTROLLER_HPP_