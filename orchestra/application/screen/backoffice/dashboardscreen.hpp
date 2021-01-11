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
#ifndef ORCHESTRA_APPLICATION_SCREEN_BACKOFFICE_DASHBOARDSCREEN_HPP_
#define ORCHESTRA_APPLICATION_SCREEN_BACKOFFICE_DASHBOARDSCREEN_HPP_
#include <future>
#include <memory>
#include <string>
#include <domain/dashboard/interface/dashboardiface.hpp>
#include <domain/dashboard/interface/dashboardviewif.hpp>
#include <screeniface.hpp>
#include <entity/user.hpp>

namespace screen {
namespace backoffice {

class DashboardScreen : public ScreenInterface, public domain::dashboard::DashboardViewInterface {
 public:
    explicit DashboardScreen(const std::string& userID);
    ~DashboardScreen() = default;

    // ScreenInterface
    void show(std::promise<defines::display>* promise) override;

    // Domain interface implementation
    void showUserNotFound() override;
    void showInvalidOptionPopup() override;
    void showDataNotReadyScreen() override;

 private:
    std::string mUserID;
    entity::User mCurrentUser;
    // Dashboard options - this represents the buttons in a GUI
    enum class Options {
        LANDING,
        USER_DETAILS,
        EMPLOYEE_MGMT,
        INVENTORY_CTRL,
        CUSTOMER_MGMT,
        // add more enums here
        LOGOUT,
        APP_EXIT,
        INVALID
        // Warning! Don't add anything here.
        // New enum values must be added before LOGOUT
    };
    void menuSelection(std::promise<defines::display>* promise) const;
    void showLandingScreen() const;
    void showOptions() const;
    void showUserInformation() const;
    void invalidOptionSelected() const;
    Options getUserSelection() const;
    bool action(Options option, std::promise<defines::display>* nextScreen) const;
    domain::dashboard::DashboardControllerPtr mCoreDashboard;
};

}  // namespace backoffice
}  // namespace screen
#endif  // ORCHESTRA_APPLICATION_SCREEN_BACKOFFICE_DASHBOARDSCREEN_HPP_