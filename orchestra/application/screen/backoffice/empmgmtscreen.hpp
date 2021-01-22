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
#include <string>
#include <vector>
// Core
#include <domain/employeemgmt/interface/employeemgmtiface.hpp>
#include <domain/employeemgmt/interface/employeemgmtviewif.hpp>
#include <employeedata.hpp>
// Screens
#include "backofficescreenbase.hpp"
#include <fieldhelper.hpp>
#include <screeniface.hpp>
#include <tablehelper.hpp>

namespace screen {
namespace backoffice {

class EmployeeMgmtScreen : public ScreenInterface,
                           public BackOfficeScreenBase<domain::empmgmt::EmpMgmtControllerPtr>,
                           public domain::empmgmt::EmployeeMgmtViewInterface {
 public:
    EmployeeMgmtScreen();
    ~EmployeeMgmtScreen() = default;

    // ScreenInterface
    void show(std::promise<defines::display>* promise) override;

    // Domain interface implementation
    void showEmployeesEmptyPopup() override;
    void showDataNotReadyScreen() override;
    void showEmployeeNotFoundPopup() override;
    void showSuccessfullyRemoved(const std::string& id) override;
    void showEmployeeExists(const std::string& name) override;
    void showUserSuccessfullyCreated(const std::string& name,
                                     const std::string& userID) override;

 private:
    void showLandingScreen() const;
    void showEmployees() const;
    Options getUserSelection();
    bool action(Options option, std::promise<defines::display>* nextScreen);
    void showEmployeeInformation(bool showIndex = false) const;
    void queryEmployeesList();
    void createEmployee();
    void updateEmployee();
    void removeEmployee();
    void fillOtherEmployeeInformation(entity::Employee* employee,
                                      const std::vector<std::string>& requiredFields = {}) const;
    app::utility::TableHelper<entity::Employee> mTableHelper;
    app::utility::FieldHelper<entity::Employee> empFieldHelper;
    bool isShowingDetailsScreen;
};

}  // namespace backoffice
}  // namespace screen
#endif  // ORCHESTRA_APPLICATION_SCREEN_BACKOFFICE_EMPMGMTSCREEN_HPP_