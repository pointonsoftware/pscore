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
#ifndef CORE_DOMAIN_DASHBOARD_DASHBOARDCONTROLLER_HPP_
#define CORE_DOMAIN_DASHBOARD_DASHBOARDCONTROLLER_HPP_
#include <string>
#include "interface/dashboardiface.hpp"
#include <entity/user.hpp>

namespace domain {
namespace dashboard {

class DashboardController : public DashboardControlInterface {
 public:
    DashboardController();
    virtual ~DashboardController() = default;

    void PrintUser() override;
    void setCurrentUserId(const std::string& userID) override;
    entity::User getCurrentUserInfo() override;
 private:
    std::string mCurrentUserID;
    bool isUserValid(const entity::User& userInfo) const;
};

}  // namespace dashboard
}  // namespace domain
#endif  // CORE_DOMAIN_DASHBOARD_DASHBOARDCONTROLLER_HPP_