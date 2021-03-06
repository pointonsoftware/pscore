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
#ifndef ORCHESTRA_DATAMANAGER_INVENTORYDATA_HPP_
#define ORCHESTRA_DATAMANAGER_INVENTORYDATA_HPP_
#include <string>
#include <vector>
#include <domain/inventory/interface/inventorydataif.hpp>

namespace dataprovider {
namespace inventory {

class InventoryDataProvider : public domain::inventory::InventoryDataInterface {
 public:
    InventoryDataProvider() = default;
    virtual ~InventoryDataProvider() = default;

    std::vector<entity::Product> getProducts() override;
    void create(const entity::Product& product) override;
    void removeWithBarcode(const std::string& barcode) override;
    void update(const entity::Product& product) override;
    std::vector<entity::UnitOfMeasurement> getUOMs() override;
    void createUOM(const entity::UnitOfMeasurement& uom) override;
    void removeUOM(const std::string& id) override;
    std::vector<std::string> getCategories() override;
    void createCategory(const std::string& category) override;
    void removeCategory(const std::string& category) override;
};

}  // namespace inventory
}  // namespace dataprovider
#endif  // ORCHESTRA_DATAMANAGER_INVENTORYDATA_HPP_
