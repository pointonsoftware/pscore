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
    validationFunctions.emplace_back(std::bind(&ProductValidator::validateSKU, this));
    validationFunctions.emplace_back(std::bind(&ProductValidator::validateName, this));
    validationFunctions.emplace_back(std::bind(&ProductValidator::validateDescription, this));
    validationFunctions.emplace_back(std::bind(&ProductValidator::validateCategory, this));
    validationFunctions.emplace_back(std::bind(&ProductValidator::validateBrand, this));
    validationFunctions.emplace_back(std::bind(&ProductValidator::validateUOM, this));
    validationFunctions.emplace_back(std::bind(&ProductValidator::validateStock, this));
    validationFunctions.emplace_back(std::bind(&ProductValidator::validateStatus, this));
    validationFunctions.emplace_back(std::bind(&ProductValidator::validateOriginalPrice, this));
    validationFunctions.emplace_back(std::bind(&ProductValidator::validateSellingPrice, this));
    validationFunctions.emplace_back(std::bind(&ProductValidator::validateSupplierName, this));
    validationFunctions.emplace_back(std::bind(&ProductValidator::validateSupplierCode, this));
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
    if (checkEmptyString(mProduct.stock(), FIELD_STOCK, "Stocks") != ValidationStatus::S_OK) {
            return ValidationStatus::S_EMPTY;
    }
    if (!utility::isNumber(mProduct.stock())) {
        addError(FIELD_STOCK, "Invalid stocks value.");
        return ValidationStatus::S_INVALID_STRING;
    }
    return ValidationStatus::S_OK;
}

ValidationStatus ProductValidator::validateStatus() {
    return checkEmptyString(mProduct.status(), FIELD_PSTATUS, "Status");
}

ValidationStatus ProductValidator::validateOriginalPrice() {
    if (checkEmptyString(mProduct.originalPrice(), FIELD_OPRICE, "Original Price")
        != ValidationStatus::S_OK) {
            return ValidationStatus::S_EMPTY;
    }
    if (mProduct.originalPrice().find(".") == std::string::npos) {
        addError(FIELD_OPRICE, "Original price must contain a decimal point.");
        return ValidationStatus::S_INVALID_STRING;
    }
    if (!utility::isDouble(mProduct.originalPrice())) {
        addError(FIELD_OPRICE, "Original price must be a valid value.");
        return ValidationStatus::S_INVALID_STRING;
    }
    if (mProduct.originalPrice().substr(mProduct.originalPrice().find(".")).length()
        != Product::PRICE_DECIMAL_POINTS + 1) {  // + 1 since std::find also counts "."
        addError(FIELD_OPRICE, "Original price must only have two decimal places.");
        return ValidationStatus::S_INVALID_STRING;
    }
    return ValidationStatus::S_OK;
}

ValidationStatus ProductValidator::validateSellingPrice() {
    if (checkEmptyString(mProduct.sellPrice(), FIELD_SPRICE, "Selling Price")
        != ValidationStatus::S_OK) {
            return ValidationStatus::S_EMPTY;
    }
    if (mProduct.sellPrice().find(".") == std::string::npos) {
        addError(FIELD_SPRICE, "Selling price must contain a decimal point.");
        return ValidationStatus::S_INVALID_STRING;
    }
    if (!utility::isDouble(mProduct.sellPrice())) {
        addError(FIELD_SPRICE, "Selling price must be a valid value.");
        return ValidationStatus::S_INVALID_STRING;
    }
    if (mProduct.sellPrice().substr(mProduct.sellPrice().find(".")).length()
        != Product::PRICE_DECIMAL_POINTS + 1) {  // + 1 since std::find also counts "."
        addError(FIELD_SPRICE, "Selling price must only have two decimal places.");
        return ValidationStatus::S_INVALID_STRING;
    }
    return ValidationStatus::S_OK;
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
