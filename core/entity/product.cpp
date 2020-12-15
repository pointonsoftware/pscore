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
#include "product.hpp"
#include <string>

namespace entity {

Product::Product(const std::string& sku,
           const std::string& name,
           const std::string& description,
           const std::string& barcode,
           const std::string& category,
           const std::string& brand,
           const std::string& uom,
           const std::string& stock,
           const std::string& status,
           const std::string& originalPrice,
           const std::string& sellPrice,
           const std::string& supplierName,
           const std::string& supplierCode)
    : mSKU(sku), mName(name), mDescription(description), mBarcode(barcode),
      mCategory(category), mBrand(brand), mUOM(uom), mStock(stock), mStatus(status),
      mOriginalPrice(originalPrice), mSellPrice(sellPrice),
      mSupplierName(supplierName), mSupplierCode(supplierCode) {
    // Empty for now
}

void Product::setName(const std::string& name) {
    mName = name;
}

void Product::setDescription(const std::string& description) {
    mDescription = description;
}

void Product::setBarcode(const std::string& barcode) {
    mBarcode = barcode;
}

void Product::setCategory(const std::string& category) {
    mCategory = category;
}

void Product::setBrand(const std::string& brand) {
    mBrand = brand;
}

void Product::setUOM(const std::string& uom) {
    mUOM = uom;
}

void Product::setStock(const std::string& stock) {
    mStock = stock;
}

void Product::setStatus(const std::string& status) {
    mStatus = status;
}

void Product::setOriginalPrice(const std::string& originalPrice) {
    mOriginalPrice = originalPrice;
}

void Product::setSellPrice(const std::string& sellPrice) {
    mSellPrice = sellPrice;
}

void Product::setSupplierName(const std::string& supplierName) {
    mSupplierName = supplierName;
}

void Product::setSupplierCode(const std::string& supplierCode) {
    mSupplierCode = supplierCode;
}

}  // namespace entity
