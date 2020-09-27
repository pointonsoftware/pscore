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
/* NOTE!
 * When updating the std::cin's of console_app, update ci/automation_input.txt as well.
*/

#include "flowcontroller.hpp"
// std
#include <iostream>
// data
#include <logindata/authdata.hpp>
// domain
#include <domain/userlogin/authcontroller.hpp>
// view
#include <viewcommon.hpp>
#include <login/authview.hpp>
// utility
#include <logger/loghelper.hpp>

namespace view {

void FlowController::run() {
    bool endRun = false;
    do {
        // Welcome to Core!
        VIEWCOMMON().showWelcomeScreen();
        showLoginScreen();
        endRun = true;
    } while (!endRun);
}

void FlowController::showLoginScreen() {
    authentication::AuthView authView;
    authView.show();
}

}  // namespace view