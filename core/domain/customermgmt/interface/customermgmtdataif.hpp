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
#ifndef CORE_DOMAIN_CUSTOMERMGMT_INTERFACE_CUSTOMERMGMTDATAIF_HPP_
#define CORE_DOMAIN_CUSTOMERMGMT_INTERFACE_CUSTOMERMGMTDATAIF_HPP_
#include <string>
#include <vector>
#include <entity/customer.hpp>

namespace domain {
namespace customermgmt {

class CustomerManagementDataInterface {
 public:
    CustomerManagementDataInterface() = default;
    virtual ~CustomerManagementDataInterface() = default;

    /*!
     * Retrieves the all customers from the database
    */
    virtual std::vector<entity::Customer> getCustomers() = 0;
    /*!
     * Create a customer
    */
    virtual void create(const entity::Customer& customer) = 0;
    /*!
     * Update a customer
    */
    virtual void update(const entity::Customer& customer) = 0;
    /*!
     * Removes the customer from the database
    */
    virtual void remove(const std::string& id) = 0;
};

}  // namespace customermgmt
}  // namespace domain
#endif  // CORE_DOMAIN_CUSTOMERMGMT_INTERFACE_CUSTOMERMGMTDATAIF_HPP_