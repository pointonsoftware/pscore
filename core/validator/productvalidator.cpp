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
#include "productvalidator.hpp"
#include <string>
#include <general.hpp>  // pscore utility

namespace entity {
namespace validator {

ProductValidator::ProductValidator(const Product& product) : mProduct(product) {
    validationFunctions.emplace_back(std::bind(&ProductValidator::validateBarcode, this));
    validate();
}

ValidationStatus ProductValidator::validateBarcode() {
    return checkEmptyString(mProduct.barcode(), FIELD_BCODE, "Barcode");
}

ValidationStatus ProductValidator::validateSKU() {
    return checkEmptyString(mProduct.sku(), FIELD_SKU, "SKU");
}

ValidationStatus ProductValidator::validateName() {
    return checkEmptyString(mProduct.name(), FIELD_PNAME, "Product Name");
}

ValidationStatus ProductValidator::validateDescription() {
    // Todo (code) Empty for now. Maybe check for max length?
    return ValidationStatus::S_OK;
}

ValidationStatus ProductValidator::validateCategory() {
    return checkEmptyString(mProduct.category(), FIELD_CTGR, "Category");
}

ValidationStatus ProductValidator::validateBrand() {
    return checkEmptyString(mProduct.brand(), FIELD_BRAND, "Brand");
}

ValidationStatus ProductValidator::validateUOM() {
    return checkEmptyString(mProduct.uom(), FIELD_UOM, "Unit of Measurement");
}

ValidationStatus ProductValidator::validateStock() {
    return checkEmptyString(mProduct.stock(), FIELD_STOCK, "Stocks");
}

ValidationStatus ProductValidator::validateStatus() {
    return checkEmptyString(mProduct.status(), FIELD_PSTATUS, "Status");
}

ValidationStatus ProductValidator::validateOriginalPrice() {
    return checkEmptyString(mProduct.originalPrice(), FIELD_OPRICE, "Original Price");
}

ValidationStatus ProductValidator::validateSellingPrice() {
    return checkEmptyString(mProduct.sellPrice(), FIELD_SPRICE, "Selling Price");
}

ValidationStatus ProductValidator::validateSupplierName() {
    return checkEmptyString(mProduct.supplierName(), FIELD_SPNAME, "Supplier Name");
}

ValidationStatus ProductValidator::validateSupplierCode() {
    return checkEmptyString(mProduct.supplierCode(), FIELD_SPCODE, "Supplier Code");
}

ValidationStatus ProductValidator::checkEmptyString(const std::string& str,
                                                    const std::string& field,
                                                    const std::string& fieldString) {
    if (str.empty()) {
        addError(field, fieldString + " cannot be empty.");
        return ValidationStatus::S_EMPTY;
    }
    return ValidationStatus::S_OK;
}

}  // namespace validator
}  // namespace entity
