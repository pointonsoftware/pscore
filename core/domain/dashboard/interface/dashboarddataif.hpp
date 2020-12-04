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
#ifndef CORE_DOMAIN_DASHBOARD_INTERFACE_DASHBOARDDATAIF_HPP_
#define CORE_DOMAIN_DASHBOARD_INTERFACE_DASHBOARDDATAIF_HPP_
#include <string>
#include <entity/user.hpp>
#include <entity/employee.hpp>

namespace domain {
namespace dashboard {

class DashboardDataInterface {
 public:
    DashboardDataInterface() = default;
    virtual ~DashboardDataInterface() = default;
    /*!
     * entity::User getUserByID(const std::string& userID)
     * Looks for the user with userid
     * Will return user->userID empty if user is not found.
     *
     * [in] input userID
     * [return] user entity
    */
    virtual entity::User getUserByID(const std::string& userID) = 0;
    /*!
     * entity::Employee getEmployeeInformation(const std::string& employeeID)
     * Used to retrieve the user information from employee database
     * The employeeID parameter must be coming from getUserByID() API
     *
     * [in] employeeID
     * [return] employee entity
    */
    virtual entity::Employee getEmployeeInformation(const std::string& employeeID) = 0;
};

}  // namespace dashboard
}  // namespace domain
#endif  // CORE_DOMAIN_DASHBOARD_INTERFACE_DASHBOARDDATAIF_HPP_