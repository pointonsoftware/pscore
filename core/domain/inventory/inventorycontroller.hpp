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
#ifndef CORE_DOMAIN_INVENTORY_INVENTORYCONTROLLER_HPP_
#define CORE_DOMAIN_INVENTORY_INVENTORYCONTROLLER_HPP_
#include <memory>
#include <string>
#include <map>
#include <vector>
#include "interface/inventoryiface.hpp"
#include <domain/common/basecontroller.hpp>
// Entity
#include <entity/product.hpp>

namespace domain {
namespace inventory {

typedef std::map<std::string, std::string> ValidationErrors;

class InventoryController : public InventoryControlInterface,
                            public BaseController<InventoryDataInterface,
                                                  InventoryViewInterface,
                                                  entity::Product>  {
 public:
    explicit InventoryController(const InventoryDataPtr& data,
                                 const InventoryViewPtr& view);
    ~InventoryController() = default;

    std::vector<entity::Product> list() override;
    entity::Product getProduct(const std::string& barcode) override;
    INVENTORYAPISTATUS save(const entity::Product& product,
                            std::map<std::string, std::string>* validationResult) override;
    INVENTORYAPISTATUS remove(const std::string& barcode) override;

 private:
    void create(const entity::Product& product);
    void update(const entity::Product& product);
};

}  // namespace inventory
}  // namespace domain

#endif  // CORE_DOMAIN_INVENTORY_INVENTORYCONTROLLER_HPP_