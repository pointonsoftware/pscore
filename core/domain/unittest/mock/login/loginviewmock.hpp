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
#ifndef CORE_DOMAIN_UNITTEST_MOCK_LOGIN_LOGINVIEWMOCK_HPP_
#define CORE_DOMAIN_UNITTEST_MOCK_LOGIN_LOGINVIEWMOCK_HPP_
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <domain/userlogin/interface/loginviewif.hpp>
#include <entity/user.hpp>

namespace domain {
namespace login {

class LoginViewMock : public LoginViewIface {
 public:
    LoginViewMock() = default;
    ~LoginViewMock() = default;

    MOCK_METHOD(void, loginSuccessful, (const entity::User& userInfo));
    MOCK_METHOD(void, showInvalidPINScreen, ());
    MOCK_METHOD(void, showUserNotFoundScreen, ());
    MOCK_METHOD(void, showDataNotReadyScreen, ());
};

}  // namespace login
}  // namespace domain
#endif  // CORE_DOMAIN_UNITTEST_MOCK_LOGIN_LOGINVIEWMOCK_HPP_