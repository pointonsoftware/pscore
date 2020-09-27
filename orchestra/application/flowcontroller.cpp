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
#include <logindata.hpp>
// domain
#include <domain/userlogin/logincontroller.hpp>
// view
#include <screencommon.hpp>
#include <login/loginscreen.hpp>
// utility
#include <logger/loghelper.hpp>

namespace view {

// todo (flow refactor):
// define the screen enums
// those screen enums will be returned by the view (thru std::future/promise)
// the we go back to our switch where the screen enums are our keys/cases
// This way the flow controller will decide which screen to go next

void FlowController::run() {
    bool endRun = false;
    do {
        // Welcome to Core!
        SCREENCOMMON().showWelcomeScreen();
        // todo (flow refactor):
        // below must be spawned by a thread and must return
        // let the flow controller decide which screen to go next
        showLoginScreen();
        endRun = true;
    } while (!endRun);

    /*!
     * Todo (flow refactor):
     * screen_enum nextScreen = login_screen
     * do {
     *   nextScreen = [] () {
     *      switch (nextScreen) {
     *          case login_screen:
     *             return = showLoginScreen()
     *          case exit:
     *            break;
     *      }
     *   }();
     * } while ( nextScreen != screen_enum::exit);
     *
     *
    */
}

// todo (flow refactor):
// screen_enum FlowController::showLoginScreen() {
//     std::promise<screen_enum> promiseObject;
//     sd::future<screen_enum> futureObject = promiseObject.get_future();
//     login::LoginScreen loginScreen;
//     std::thread th(&loginScreen, show, (std::promise<screen_enum>* (&promiseObject));
//     // the promise object must be set somewhere inside the loginScreen
//     // thru promiseObject->set_value(screenvalue);
//     th.join();
//     return future.get()
// }

void FlowController::showLoginScreen() {
    login::LoginScreen loginScreen;
    loginScreen.show();
}

}  // namespace view