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
// screens
#include <login/loginscreen.hpp>
#include <backoffice/accountingscreen.hpp>
#include <backoffice/customermgmtscreen.hpp>
#include <backoffice/dashboardscreen.hpp>
#include <backoffice/empmgmtscreen.hpp>
#include <backoffice/inventoryscreen.hpp>
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
    defines::display nextScreen = defines::display::LOGIN;
    LOG_INFO("System startup");
    LOG_INFO("Core library version: %s", SCREENCOMMON().getCoreVersion().c_str());
    do {
        // This promise is used for setting the future screen
        std::promise<defines::display> promise;
        std::future<defines::display> futureScreen = promise.get_future();
        // Display the queued screen, and send the promise
        show(nextScreen, &promise);
        // Here, we set the next screen to whatever is returned from the promise
        nextScreen = futureScreen.get();
    } while (nextScreen != defines::display::EXIT);
    LOG_INFO("Exited the console app");
}

void FlowController::show(const defines::display& screenToDisplay,
                         std::promise<defines::display>* promise) {
    std::shared_ptr<screen::ScreenInterface> screen;
    switch (screenToDisplay) {
        case defines::display::LOGIN:
            LOG_DEBUG("screen: Login");
            screenshared::currentUserId = "";  // Reset the current userID
            screen = std::make_shared<login::LoginScreen>();
            break;
        case defines::display::DASHBOARD:
            LOG_DEBUG("screen: Dashboard");
            screen = std::make_shared<backoffice::DashboardScreen>(screenshared::currentUserId);
            break;
        case defines::display::EMPMGMT:
            LOG_DEBUG("screen: Employee management");
            screen = std::make_shared<backoffice::EmployeeMgmtScreen>();
            break;
        case defines::display::INVENTORY:
            LOG_DEBUG("screen: Inventory management");
            screen = std::make_shared<backoffice::InventoryScreen>();
            break;
        case defines::display::CUSTMGMT:
            LOG_DEBUG("screen: Customer management");
            screen = std::make_shared<backoffice::CustomerMgmtScreen>();
            break;
        case defines::display::ACCNTING:
            LOG_DEBUG("screen: Accounting");
            screen = std::make_shared<backoffice::AccountingScreen>();
            break;
        case defines::display::EXIT:  // fall-through
        default:
            // this case should not happen
            promise->set_value(defines::display::EXIT);
            break;
    }

    // Actual screen showing
    spawnScreen(screen, promise);

    // Post Processing
    if (screenToDisplay == defines::display::LOGIN) {
        // Get the current user ID if login is successful
        screenshared::currentUserId =
        std::dynamic_pointer_cast<login::LoginScreen>(screen)->getUserID();
    }
}

void FlowController::spawnScreen(std::weak_ptr<screen::ScreenInterface> screen,
                                std::promise<defines::display>* promise) {
    auto screenPtr = screen.lock();
    std::thread spawnScreenProcess(&screen::ScreenInterface::show, screenPtr.get(), promise);
    spawnScreenProcess.join();
}

}  // namespace screen