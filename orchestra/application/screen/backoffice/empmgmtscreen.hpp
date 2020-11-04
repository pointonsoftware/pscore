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
#include <memory>
#include <string>
#include <vector>
#include <domain/employeemgmt/interface/employeemgmtviewif.hpp>
#include <screeniface.hpp>
// core
#include <domain/employeemgmt/interface/employeemgmtiface.hpp>

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
    void showEmployeeNotFoundPopup() override;
    void showSuccessfullyRemoved(const std::string& id) override;

 private:
     // Screen options - this represents the buttons in a GUI
    enum class Options {
        LANDING,
        DASHBOARD,
        EMPLOYEE_DETAILS,
        EMPLOYEE_CREATE,
        EMPLOYEE_REMOVE,
        EMPLOYEE_UPDATE,
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
    Options getUserSelection();
    bool action(Options option, std::promise<defines::display>* nextScreen);
    void invalidOptionSelected() const;
    void showEmployeeInformation() const;
    void queryEmployeesList();
    void createEmployee();
    void removeEmployee();
    std::vector<entity::Employee> mEmployeesGUITable;  // Represents the GUI employees-table
    unsigned int mSelectedEmployeeIndex = 0;  // 1-based index
    std::unique_ptr<domain::empmgmt::EmployeeMgmtControlInterface> mCoreEmployeeMgmt;
};

}  // namespace backoffice
}  // namespace screen
#endif  // ORCHESTRA_APPLICATION_SCREEN_BACKOFFICE_EMPMGMTSCREEN_HPP_