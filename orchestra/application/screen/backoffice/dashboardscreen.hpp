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
#include <string>
#include <future>
#include <domain/dashboard/interface/dashboardviewif.hpp>
#include <screeniface.hpp>

namespace screen {
namespace backoffice {

class DashboardScreen : public ScreenInterface, public domain::dashboard::DashboardViewInterface {
 public:
    explicit DashboardScreen(const std::string& userID);
    ~DashboardScreen() = default;

    // ScreenInterface
    void show(std::promise<screen::display>* promise) override;

    // Domain interface implementation
    void showUserNotFound() override;
    void showInvalidOptionPopup() override;
    void showDataNotReadyScreen() override;
 private:
    std::string mUserID;
};

}  // namespace backoffice
}  // namespace screen
#endif  // ORCHESTRA_APPLICATION_SCREEN_BACKOFFICE_DASHBOARDSCREEN_HPP_