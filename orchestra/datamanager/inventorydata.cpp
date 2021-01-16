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
#include "inventorydata.hpp"
#include <algorithm>
#include <string>
#include <vector>
#include <storage/stackdb.hpp>

namespace dataprovider {
namespace inventory {

std::vector<entity::Product> InventoryDataProvider::getProducts() {
    // SELECT PRODUCTS
    std::vector<entity::Product> products;
    for (const db::StackDB::ProductTableItem& temp : DATABASE().SELECT_PRODUCT_TABLE()) {
        entity::Product product(
            temp.barcode,
            temp.sku,
            temp.name,
            temp.description,
            temp.category,
            temp.brand,
            temp.uom,
            temp.stock,
            temp.status,
            temp.original_price,
            temp.sell_price,
            temp.supplier_name,
            temp.supplier_code);
        products.emplace_back(product);
    }
    return products;
}

void InventoryDataProvider::create(const entity::Product& product) {
    // INSERT INTO to the database
    DATABASE().SELECT_PRODUCT_TABLE().emplace_back(db::StackDB::ProductTableItem {
            product.barcode(),
            product.sku(),
            product.name(),
            product.description(),
            product.category(),
            product.brand(),
            product.uom(),
            product.stock(),
            product.status(),
            product.originalPrice(),
            product.sellPrice(),
            product.supplierName(),
            product.supplierCode()});
}

void InventoryDataProvider::removeWithBarcode(const std::string& barcode) {
    // Delete in PRODUCTS
    DATABASE().SELECT_PRODUCT_TABLE().erase(
        std::remove_if(DATABASE().SELECT_PRODUCT_TABLE().begin(),
                    DATABASE().SELECT_PRODUCT_TABLE().end(),
                    [&](const db::StackDB::ProductTableItem& e) {
                        return e.barcode == barcode;
                    }),
        DATABASE().SELECT_PRODUCT_TABLE().end());
}

void InventoryDataProvider::update(const entity::Product& product) {
    // UPDATE data in the database
    std::vector<db::StackDB::ProductTableItem>::iterator it =
        std::find_if(DATABASE().SELECT_PRODUCT_TABLE().begin(),
                     DATABASE().SELECT_PRODUCT_TABLE().end(),
                     [&product](const db::StackDB::ProductTableItem& e) {
                                // We only match the product barcode for updating
                                return e.barcode == product.barcode();
                     });
    if (it == DATABASE().SELECT_PRODUCT_TABLE().end()) {
        // Not found
        return;
    }
    // Actual update
    *it = db::StackDB::ProductTableItem {
            product.barcode(),
            product.sku(),
            product.name(),
            product.description(),
            product.category(),
            product.brand(),
            product.uom(),
            product.stock(),
            product.status(),
            product.originalPrice(),
            product.sellPrice(),
            product.supplierName(),
            product.supplierCode() };
}

std::vector<entity::UnitOfMeasurement> InventoryDataProvider::getUOMs() {
    // SELECT UOMs
    std::vector<entity::UnitOfMeasurement> uoms;
    for (const db::StackDB::UOMTableItem& temp : DATABASE().SELECT_UOM_TABLE()) {
        uoms.emplace_back(entity::UnitOfMeasurement(temp.ID, temp.unit_name, temp.abbreviation));
    }
    return uoms;
}

void InventoryDataProvider::createUOM(const entity::UnitOfMeasurement& uom) {
    // INSERT INTO to the database
    DATABASE().SELECT_UOM_TABLE().emplace_back(db::StackDB::UOMTableItem{
                                               uom.ID(), uom.name(), uom.abbreviation()});
}

void InventoryDataProvider::removeUOM(const std::string& id) {
    // Delete in UOMs
    DATABASE().SELECT_UOM_TABLE().erase(
        std::remove_if(DATABASE().SELECT_UOM_TABLE().begin(),
                    DATABASE().SELECT_UOM_TABLE().end(),
                    [&](const db::StackDB::UOMTableItem& e) {
                        return e.ID == id;
                    }),
        DATABASE().SELECT_UOM_TABLE().end());
}

}  // namespace inventory
}  // namespace dataprovider

