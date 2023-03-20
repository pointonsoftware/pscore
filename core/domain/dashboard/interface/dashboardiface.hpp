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
#ifndef CORE_DOMAIN_DASHBOARD_INTERFACE_DASHBOARDIFACE_HPP_
#define CORE_DOMAIN_DASHBOARD_INTERFACE_DASHBOARDIFACE_HPP_
#include <memory>
#include <string>
#include "dashboarddataif.hpp"
#include "dashboardviewif.hpp"
#include <domain/common/librarycommon.hpp>
#include <entity/user.hpp>
#include <entity/employee.hpp>

namespace domain {
namespace dashboard {

class DashboardControlInterface {
 public:
    DashboardControlInterface() = default;
    virtual ~DashboardControlInterface() = default;

    /**
     *  Sets the current user ID
     *  Warning: it is the caller's responsibility to provide a valid userID
    */
    virtual void setCurrentUserId(const std::string& userID) = 0;
    /**
     *  Returns the current user
     *  Note: Has to be paired with setCurrentUserId(); otherwise, will return empty
    */
    virtual entity::User getCurrentUser() = 0;
    /**
     *  Returns more user information through the employee entity
     *  Note: Has to be paired with setCurrentUserId() and the user must have an employeeID;
     *        otherwise, will return empty.
    */
    virtual entity::Employee getUserDetails(const entity::User& user) = 0;
};

typedef std::shared_ptr<DashboardDataInterface> DashboardDataPtr;
typedef std::shared_ptr<DashboardViewInterface> DashboardViewPtr;
typedef std::unique_ptr<DashboardControlInterface> DashboardControllerPtr;

// Lib APIs
CORE_API DashboardControllerPtr createDashboardModule
                    (const DashboardDataPtr& data, const DashboardViewPtr& view);

}  // namespace dashboard
}  // namespace domain

#endif  // CORE_DOMAIN_DASHBOARD_INTERFACE_DASHBOARDIFACE_HPP_