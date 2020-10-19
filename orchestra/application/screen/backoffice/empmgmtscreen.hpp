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
#ifndef ORCHESTRA_APPLICATION_SCREEN_BACKOFFICE_EMPMGMTSCREEN_HPP_
#define ORCHESTRA_APPLICATION_SCREEN_BACKOFFICE_EMPMGMTSCREEN_HPP_
#include <future>
#include <domain/employeemgmt/interface/employeemgmtviewif.hpp>
#include <screeniface.hpp>

namespace screen {
namespace backoffice {

class EmployeeMgmtScreen : public ScreenInterface,
                           public domain::empmgmt::EmployeeMgmtViewInterface {
 public:
    EmployeeMgmtScreen() = default;
    ~EmployeeMgmtScreen() = default;

    // ScreenInterface
    void show(std::promise<defines::display>* promise) override;

    // Domain interface implementation
    void showEmployeesEmptyPopup() override;
    void showDataNotReadyScreen() override;

 private:
     // Screen options - this represents the buttons in a GUI
    enum class Options {
        LANDING,
        DASHBOARD,
        EMPLOYEE_DETAILS,
        // add more enums here
        LOGOUT,
        APP_EXIT,
        INVALID
        // Warning! Don't add anything here.
        // New enum values must be added before LOGOUT
    };
    void showLandingScreen() const;
    void showEmployees() const;
    void showOptions() const;
    Options getUserSelection() const;
    bool action(Options option, std::promise<defines::display>* nextScreen) const;
    void invalidOptionSelected() const;
    void showEmployeeInformation() const;
};

}  // namespace backoffice
}  // namespace screen
#endif  // ORCHESTRA_APPLICATION_SCREEN_BACKOFFICE_EMPMGMTSCREEN_HPP_