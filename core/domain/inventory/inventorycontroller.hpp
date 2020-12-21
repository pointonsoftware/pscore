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

// Entity
#include <entity/product.hpp>

namespace domain {
namespace inventory {

typedef std::map<std::string, std::string> ValidationErrors;

class InventoryController : public InventoryControlInterface {
 public:
    explicit InventoryController(const std::shared_ptr<InventoryDataInterface>& data,
                                 const std::shared_ptr<InventoryViewInterface>& view);
    ~InventoryController() = default;

 private:
    std::shared_ptr<InventoryDataInterface> mDataProvider;
    std::shared_ptr<InventoryViewInterface> mView;
    std::vector<entity::Product> mCachedList;  // List of employees
};

}  // namespace inventory
}  // namespace domain

#endif  // CORE_DOMAIN_INVENTORY_INVENTORYCONTROLLER_HPP_