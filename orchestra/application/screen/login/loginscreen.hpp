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
#ifndef ORCHESTRA_APPLICATION_SCREEN_LOGIN_LOGINSCREEN_HPP_
#define ORCHESTRA_APPLICATION_SCREEN_LOGIN_LOGINSCREEN_HPP_
#include <future>
#include <string>
// core
#include <domain/userlogin/interface/loginiface.hpp>
#include <domain/userlogin/interface/loginviewif.hpp>
#include <screeniface.hpp>

namespace screen {
namespace login {

class LoginScreen : public screen::ScreenInterface, public domain::login::LoginViewIface {
 public:
    LoginScreen() = default;
    ~LoginScreen() = default;

    // Public API

    /*!
     * Returns the userID of the logged user
    */
    std::string getUserID() const;

    // ScreenInterface
    void show(std::promise<defines::display>* promise) override;

    // Domain interface implementation
    void showUserNotFoundScreen() override;
    void showDataNotReadyScreen() override;

 private:
    std::string mUserID;
    // Return true if successful
    bool onLogin(const std::string& id, const std::string& pin);
};

}  // namespace login
}  // namespace screen
#endif  // ORCHESTRA_APPLICATION_SCREEN_LOGIN_LOGINSCREEN_HPP_
