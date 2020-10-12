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
#include <string>
#include <thread>
// data
#include <logindata.hpp>
// domain
#include <domain/userlogin/logincontroller.hpp>
// view
#include <screencommon.hpp>
#include <login/loginscreen.hpp>
#include <backoffice/dashboardscreen.hpp>
// utility
#include <logger/loghelper.hpp>

namespace screen {

namespace screenshared {
    /*!
     * Add variables that are shared by different screens
     * Can be used to pass parameter from one screen to next
    */
    std::string currentUserId;
}

void FlowController::run() {
    // After the welcome screen, we will display the login screen
    screen::display nextScreen = screen::display::LOGIN;

    do {
        // This promise is used for setting the future screen
        std::promise<screen::display> promise;
        std::future<screen::display> futureScreen = promise.get_future();
        // Display the queued screen, and send the promise
        show(nextScreen, &promise);
        // Here, we set the next screen to whatever is returned from the promise
        nextScreen = futureScreen.get();
    } while (nextScreen != screen::display::EXIT);
}

void FlowController::show(const screen::display& screenToDisplay,
                         std::promise<screen::display>* promise) {
    switch (screenToDisplay) {
        case screen::display::LOGIN:
            showLoginScreen(promise);
            break;
        case screen::display::DASHBOARD:
            showDashboard(promise);
            break;
        case screen::display::EXIT:  // fall-through
        default:
            // this case should not happen
            promise->set_value(screen::display::EXIT);
            break;
    }
}

void FlowController::showLoginScreen(std::promise<screen::display>* promise) {
    login::LoginScreen theScreen;
    std::thread spawnScreenProcess(&login::LoginScreen::show, &theScreen, promise);
    spawnScreenProcess.join();
    screenshared::currentUserId = theScreen.getUserID();
}

void FlowController::showDashboard(std::promise<screen::display>* promise) {
    backoffice::DashboardScreen theScreen(screenshared::currentUserId);
    std::thread spawnScreenProcess(&backoffice::DashboardScreen::show, &theScreen, promise);
    spawnScreenProcess.join();
}

}  // namespace screen