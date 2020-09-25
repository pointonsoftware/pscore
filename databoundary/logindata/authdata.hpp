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
#ifndef DATABOUNDARY_LOGINDATA_AUTHDATA_HPP_
#define DATABOUNDARY_LOGINDATA_AUTHDATA_HPP_
#include <string>
#include <domain/userlogin/interface/authdataif.hpp>

namespace dataprovider {
namespace authentication {

class AuthDataProvider : public domain::authentication::AuthDataProviderIface {
 public:
    AuthDataProvider() = default;
    virtual ~AuthDataProvider() = default;
    entity::User findUserByPin(const std::string& inputPin) override;
};

}  // namespace authentication
}  // namespace dataprovider
#endif  // DATABOUNDARY_LOGINDATA_AUTHDATA_HPP_