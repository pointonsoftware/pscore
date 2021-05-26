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
#ifndef CORE_DOMAIN_INVENTORY_INTERFACE_INVENTORYDATAIF_HPP_
#define CORE_DOMAIN_INVENTORY_INTERFACE_INVENTORYDATAIF_HPP_
#include <string>
#include <vector>
#include <entity/product.hpp>
#include <entity/uom.hpp>

namespace domain {
namespace inventory {

class InventoryDataInterface {
 public:
    InventoryDataInterface() = default;
    virtual ~InventoryDataInterface() = default;

    /**
     *  Retrieves the all the products from the database
     */
    virtual std::vector<entity::Product> getProducts() = 0;
    /**
     *  Create a product
     */
    virtual void create(const entity::Product& product) = 0;
    /**
     *  Update a product
     */
    virtual void update(const entity::Product& product) = 0;
    /**
     *  Removes the product from the database
     */
    virtual void removeWithBarcode(const std::string& barcode) = 0;
    /**
     *  Returns all the registered UOMs
     */
    virtual std::vector<entity::UnitOfMeasurement> getUOMs() = 0;
    /**
     *  Add a unit of measurement
     */
    virtual void createUOM(const entity::UnitOfMeasurement& uom) = 0;
    /**
     *  Remove a unit of measurement
     */
    virtual void removeUOM(const std::string& id) = 0;
    /**
     *  Returns the categories
     */
    virtual std::vector<std::string> getCategories() = 0;
    /**
     *  Add a category
     */
    virtual void createCategory(const std::string& category) = 0;
    /**
     *  Remove a category
     */
    virtual void removeCategory(const std::string& category) = 0;
};

}  // namespace inventory
}  // namespace domain
#endif  // CORE_DOMAIN_INVENTORY_INTERFACE_INVENTORYDATAIF_HPP_