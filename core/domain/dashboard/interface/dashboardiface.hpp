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
#include <domain/librarycommon.hpp>
#include <entity/user.hpp>

namespace domain {
namespace dashboard {
/*!
 * Note: If you add/update a function in this interface, please also update the mock class
*/
enum class DASHSTATUS {
    SUCCESS       = 0,
    FAILED        = 1,
    UNINITIALIZED = 2
};

class DashboardControlInterface {
 public:
    DashboardControlInterface() = default;
    virtual ~DashboardControlInterface() = default;

    /*!
     * Sets the current user ID
     * Warning: it is the caller's responsibility to provide a valid userID
    */
    virtual void setCurrentUserId(const std::string& userID) = 0;
    /*!
     * Returns the current user info
     * Note: Has to be paired with setCurrentUserId(), otherwise will return empty
    */
    virtual entity::User getCurrentUserInfo() = 0;
};

// Lib APIs
extern "C" CORE_API std::unique_ptr<DashboardControlInterface> createDashboardModule(
    const std::shared_ptr<DashboardDataInterface>& data,
    const std::shared_ptr<DashboardViewInterface>& view);

}  // namespace dashboard
}  // namespace domain



#endif  // CORE_DOMAIN_DASHBOARD_INTERFACE_DASHBOARDIFACE_HPP_