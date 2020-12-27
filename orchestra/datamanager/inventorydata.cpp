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

}  // namespace inventory
}  // namespace dataprovider

