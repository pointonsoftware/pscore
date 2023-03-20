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
#include <map>
#include <memory>
#include <string>
#include <vector>
#include "inventorydataif.hpp"
#include "inventoryviewif.hpp"
#include <domain/common/librarycommon.hpp>

namespace domain {
namespace inventory {

enum class INVENTORYAPISTATUS {
    SUCCESS       = 0x00,
    FAILED        = 0x01,
    UNINITIALIZED = 0x02,
    NOT_FOUND     = 0x03
};

class InventoryControlInterface {
 public:
    InventoryControlInterface() = default;
    virtual ~InventoryControlInterface() = default;
    /**
     *  Gets the list of all products
     */
    virtual std::vector<entity::Product> list() = 0;
    /**
     *  Retrieves a product with the barcode
     */
    virtual entity::Product getProduct(const std::string& barcode) = 0;
    /**
     *  Used to create or update a product
     *  - Creates the product if the barcode does not exist in the database
     *  - Updates the product using the barcode
     *  @param [in] - product data
     *  @param [out] - validation result (map[field, error message])
     *
     *  Note: This will reset the map container
     */
    virtual INVENTORYAPISTATUS save(const entity::Product& product,
                                    std::map<std::string, std::string>* validationResult) = 0;
    /**
     * Deletes a product
     */
    virtual INVENTORYAPISTATUS remove(const std::string& barcode) = 0;
    /**
     *  Returns the unit of measurement list
     */
    virtual std::vector<entity::UnitOfMeasurement> getMeasurementList() = 0;
    /**
     *  Used to add a unit of measurement
     *  Note: Must be paired with getMeasurementList()
     */
    virtual INVENTORYAPISTATUS save(const entity::UnitOfMeasurement& uom) = 0;
    /**
     *  Used to delete a unit of measurement
     *  Note: Must be paired with getMeasurementList()
     */
    virtual INVENTORYAPISTATUS removeUOM(const std::string& id) = 0;
    /**
     *  Returns the list of categories
     */
    virtual std::vector<std::string> getCategoryList() = 0;
    /**
     *  Used to add a category
     *  @param category name
     */
    virtual INVENTORYAPISTATUS addCategory(const std::string& category) = 0;
    /**
     *  Used to remove a category
     *  @param category name
     */
    virtual INVENTORYAPISTATUS removeCategory(const std::string& category) = 0;
};

typedef std::shared_ptr<InventoryDataInterface> InventoryDataPtr;
typedef std::shared_ptr<InventoryViewInterface> InventoryViewPtr;
typedef std::unique_ptr<InventoryControlInterface> InventoryControllerPtr;

// Lib APIs
CORE_API InventoryControllerPtr createInventoryModule
                    (const InventoryDataPtr& data, const InventoryViewPtr& view);

}  // namespace inventory
}  // namespace domain
#endif  // CORE_DOMAIN_INVENTORY_INTERFACE_INVENTORYIFACE_HPP_