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
#ifndef APPLICATION_SCREEN_LOGIN_LOGINSCREEN_HPP_
#define APPLICATION_SCREEN_LOGIN_LOGINSCREEN_HPP_
#include <string>
#include <domain/userlogin/interface/loginviewif.hpp>
#include <screeniface.hpp>

namespace view {
namespace login {

class LoginScreen : public screen::ScreenInterface, public domain::login::LoginViewIface {
 public:
    LoginScreen() = default;
    ~LoginScreen() = default;

    void show() override;
    void loginSuccessful(const entity::User& userInfo) override;
    void showInvalidPINScreen() override;
    void showUserNotFoundScreen() override;
    void showDataNotReadyScreen() override;
};

}  // namespace login
}  // namespace view
#endif  // APPLICATION_SCREEN_LOGIN_LOGINSCREEN_HPP_