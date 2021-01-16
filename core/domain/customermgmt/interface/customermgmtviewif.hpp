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
#ifndef CORE_DOMAIN_CUSTOMERMGMT_INTERFACE_CUSTOMERMGMTVIEWIF_HPP_
#define CORE_DOMAIN_CUSTOMERMGMT_INTERFACE_CUSTOMERMGMTVIEWIF_HPP_
#include <string>

namespace domain {
namespace customermgmt {

class CustomerManagementViewInterface {
 public:
    CustomerManagementViewInterface() = default;
    virtual ~CustomerManagementViewInterface() = default;

    /**
     *  show customer list is empty popup
     */
    virtual void showListIsEmptyPopup() = 0;
    /**
     *  showDataNotReadyScreen
     */
    virtual void showDataNotReadyScreen() = 0;
    /**
     *  showSuccessfullyRemoved
     */
    virtual void showSuccessfullyRemoved(const std::string& customerName) = 0;
};

}  // namespace customermgmt
}  // namespace domain
#endif  // CORE_DOMAIN_CUSTOMERMGMT_INTERFACE_CUSTOMERMGMTVIEWIF_HPP_