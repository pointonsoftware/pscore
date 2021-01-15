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
#ifndef CORE_DOMAIN_CUSTOMERMGMT_INTERFACE_CUSTOMERMGMTIFACE_HPP_
#define CORE_DOMAIN_CUSTOMERMGMT_INTERFACE_CUSTOMERMGMTIFACE_HPP_
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "customermgmtdataif.hpp"
#include "customermgmtviewif.hpp"
#include <domain/common/librarycommon.hpp>
#include <entity/customer.hpp>

namespace domain {
namespace customermgmt {

enum class CUSTOMERMGMTAPISTATUS {
    SUCCESS       = 0x00,
    FAILED        = 0x01,
    UNINITIALIZED = 0x02,
    NOT_FOUND     = 0x03
};

class CustomerManagementControlInterface {
 public:
    CustomerManagementControlInterface() = default;
    virtual ~CustomerManagementControlInterface() = default;
    /**
     *  Gets the list of all customers
     */
    virtual std::vector<entity::Customer> list() = 0;
    /**
     *  Retrieves a customer
     */
    virtual entity::Customer get(const std::string& id) = 0;
    /**
     *  Used to create or update a customer
     *  - Creates the customer if the customerID does not exist in the database
     *  - Updates the customer using the customerID
     *  @param [in] - customer data
     *  @param [out] - validation result (map[field, error message])
     *
     *  Note: This will reset the map container
     */
    virtual CUSTOMERMGMTAPISTATUS save(const entity::Customer& customer,
                                       std::map<std::string, std::string>* validationResult) = 0;
    /**
     *  Deletes a customer
     */
    virtual CUSTOMERMGMTAPISTATUS remove(const std::string& id) = 0;
};

typedef std::shared_ptr<CustomerManagementDataInterface> CustomerMgmtDataPtr;
typedef std::shared_ptr<CustomerManagementViewInterface> CustomerMgmtViewPtr;
typedef std::unique_ptr<CustomerManagementControlInterface> CustomerMgmtCtrlPtr;

// Lib APIs
extern "C" CORE_API CustomerMgmtCtrlPtr createCustomerMgmtModule
                    (const CustomerMgmtDataPtr& data, const CustomerMgmtViewPtr& view);

}  // namespace customermgmt
}  // namespace domain
#endif  // CORE_DOMAIN_CUSTOMERMGMT_INTERFACE_CUSTOMERMGMTIFACE_HPP_