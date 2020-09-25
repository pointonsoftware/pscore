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
#ifndef MOCK_LOGIN_AUTHDATAMOCK_HPP_
#define MOCK_LOGIN_AUTHDATAMOCK_HPP_
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <domain/userlogin/interface/authdataif.hpp>
#include <entity/user.hpp>

namespace domain {
namespace authentication {

class AuthDataMock : public AuthDataProviderIface {
 public:
    AuthDataMock() = default;
    ~AuthDataMock() = default;
    MOCK_METHOD(entity::User, findUserByPin, (const std::string& inputPin));
};

}  // namespace authentication
}  // namespace domain

#endif  // MOCK_LOGIN_AUTHDATAMOCK_HPP_