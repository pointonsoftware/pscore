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
#ifndef ORCHESTRA_DATAMANAGER_LOGINDATA_HPP_
#define ORCHESTRA_DATAMANAGER_LOGINDATA_HPP_
#include <string>
#include <domain/userlogin/interface/logindataif.hpp>

namespace dataprovider {
namespace login {

class LoginDataProvider : public domain::login::LoginDataProviderIface {
 public:
    LoginDataProvider() = default;
    virtual ~LoginDataProvider() = default;
    entity::User findUserByID(const std::string& id) override;
};

}  // namespace login
}  // namespace dataprovider
#endif  // ORCHESTRA_DATAMANAGER_LOGINDATA_HPP_
