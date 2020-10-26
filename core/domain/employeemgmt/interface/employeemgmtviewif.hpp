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
#ifndef CORE_DOMAIN_EMPLOYEEMGMT_INTERFACE_EMPLOYEEMGMTVIEWIF_HPP_
#define CORE_DOMAIN_EMPLOYEEMGMT_INTERFACE_EMPLOYEEMGMTVIEWIF_HPP_
#include <string>
#include <entity/user.hpp>

namespace domain {
namespace empmgmt {
/*!
 * Note: If you add/update a function in this interface, please also update the mock class
*/
class EmployeeMgmtViewInterface {
 public:
    EmployeeMgmtViewInterface() = default;
    virtual ~EmployeeMgmtViewInterface() = default;

    /*!
     * showEmployeesEmpty
    */
    virtual void showEmployeesEmptyPopup() = 0;
    /*!
     * showDataNotReadyScreen
    */
    virtual void showDataNotReadyScreen() = 0;
    /*!
     * showEmployeeNotFoundPopup
    */
    virtual void showEmployeeNotFoundPopup() = 0;
    /*!
     * showSuccessfullyRemoved
    */
    virtual void showSuccessfullyRemoved(const std::string& id) = 0;
};

}  // namespace empmgmt
}  // namespace domain
#endif  // CORE_DOMAIN_EMPLOYEEMGMT_INTERFACE_EMPLOYEEMGMTVIEWIF_HPP_