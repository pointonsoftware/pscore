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
#ifndef CORE_DOMAIN_INVENTORY_INTERFACE_INVENTORYIFACE_HPP_
#define CORE_DOMAIN_INVENTORY_INTERFACE_INVENTORYIFACE_HPP_
#include <memory>
#include "inventorydataif.hpp"
#include "inventoryviewif.hpp"
#include <domain/librarycommon.hpp>

namespace domain {
namespace inventory {

class InventoryControlInterface {
 public:
    InventoryControlInterface() = default;
    virtual ~InventoryControlInterface() = default;
};

// Lib APIs
extern "C" CORE_API std::unique_ptr<InventoryControlInterface> createInventoryModule(
                    const std::shared_ptr<InventoryDataInterface>& data,
                    const std::shared_ptr<InventoryViewInterface>& view);

}  // namespace inventory
}  // namespace domain
#endif  // CORE_DOMAIN_INVENTORY_INTERFACE_INVENTORYIFACE_HPP_