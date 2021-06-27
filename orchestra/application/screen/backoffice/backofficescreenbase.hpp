/**************************************************************************************************
*                                            PSCORE                                               *
*                               Copyright (C) 2021 Pointon Software                               *
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
#ifndef ORCHESTRA_APPLICATION_SCREEN_BACKOFFICE_BACKOFFICESCREENBASE_HPP_
#define ORCHESTRA_APPLICATION_SCREEN_BACKOFFICE_BACKOFFICESCREENBASE_HPP_
#include <iostream>
#include <screencommon.hpp>

namespace screen {

template <class ControllerType>
class BackOfficeScreenBase {
 public:
    BackOfficeScreenBase() = default;
    virtual ~BackOfficeScreenBase() = default;

 protected:
    virtual void invalidOptionSelected() const {
        std::cout << "Sorry, that option is not yet available." << std::endl;
    }
    virtual void showOptions() const {
        std::cout << std::endl << std::endl;
        SCREENCOMMON().printColumns({"[b] - Back", "[c] - Create", "[0] - Logout"}, true, false);
        std::cout << std::endl;
    }
    // Screen options - this represents the buttons in a GUI
    enum class Options {
        LANDING,
        DASHBOARD,
        USER_PROFILE,
        EMPLOYEE_MGMT,
        INVENTORY_CTRL,
        CUSTOMER_MGMT,
        ACCOUNTING,
        OP_CREATE,
        OP_READ,
        OP_UPDATE,
        OP_DELETE,
        SALES_YESTERDAY,
        SALES_THIS_MONTH,
        // add more enums here
        LOGOUT,
        APP_EXIT,
        INVALID
        // Warning! Don't add anything here.
        // New enum values must be added before LOGOUT
    };
    ControllerType mCoreController;
};

}  // namespace screen

#endif  // ORCHESTRA_APPLICATION_SCREEN_BACKOFFICE_BACKOFFICESCREENBASE_HPP_