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
#ifndef CORE_DOMAIN_CUSTOMERMGMT_CUSTOMERMGMTCONTROLLER_HPP_
#define CORE_DOMAIN_CUSTOMERMGMT_CUSTOMERMGMTCONTROLLER_HPP_
#include <memory>
#include <string>
#include <map>
#include <vector>
#include "interface/customermgmtiface.hpp"
#include <domain/common/basecontroller.hpp>
// Entity
#include <entity/customer.hpp>

namespace domain {
namespace customermgmt {

class CustomerMgmtController : public CustomerManagementControlInterface,
                               public BaseController<CustomerManagementDataInterface,
                                                     CustomerManagementViewInterface,
                                                     entity::Customer> {
 public:
    explicit CustomerMgmtController(const CustomerMgmtDataPtr& data,
                                    const CustomerMgmtViewPtr& view);
    ~CustomerMgmtController() = default;

    std::vector<entity::Customer> list() override;
    entity::Customer get(const std::string& id) override;
    CUSTOMERMGMTAPISTATUS save(const entity::Customer& customer,
                               std::map<std::string, std::string>* validationResult) override;
    CUSTOMERMGMTAPISTATUS remove(const std::string& id) override;

 private:
    void create(const entity::Customer& customer);
    void update(const entity::Customer& customer);
};

}  // namespace customermgmt
}  // namespace domain

#endif  // CORE_DOMAIN_CUSTOMERMGMT_CUSTOMERMGMTCONTROLLER_HPP_