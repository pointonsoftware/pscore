/**************************************************************************************************
*                                            PSCORE                                               *
*                               Copyright (C) 2021 Pointon Software                               *
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
#include "saleitem.hpp"
#include <string>

namespace entity {

SaleItem::SaleItem(const std::string& saleID,
                   const std::string& productID,
                   const std::string& productName,
                   const std::string& productCategory,
                   const std::string& unitPrice,
                   const std::string& quantity,
                   const std::string& salePrice)
                   : mSaleID(saleID), mProductID(productID),
                   mProductName(productName), mProductCategory(productCategory),
                   mUnitPrice(unitPrice), mQuantity(quantity),
                   mTotalPrice(salePrice) {
    // Empty for now
}

std::string SaleItem::saleID() const {
    return mSaleID;
}

std::string SaleItem::productID() const {
    return mProductID;
}

std::string SaleItem::productName() const {
    return mProductName;
}

std::string SaleItem::productCategory() const {
    return mProductCategory;
}

std::string SaleItem::unitPrice() const {
    return mUnitPrice;
}

std::string SaleItem::quantity() const {
    return mQuantity;
}

std::string SaleItem::totalPrice() const {
    return mTotalPrice;
}

void SaleItem::setSaleID(const std::string& id) {
    mSaleID = id;
}

void SaleItem::setProductID(const std::string& id) {
    mProductID = id;
}

void SaleItem::setProductName(const std::string& name) {
    mProductName = name;
}

void SaleItem::setProductCategory(const std::string& category) {
    mProductCategory = category;
}

void SaleItem::setUnitPrice(const std::string& unitPrice) {
    mUnitPrice = unitPrice;
}

void SaleItem::setQuantity(const std::string& qty) {
    mQuantity = qty;
}

void SaleItem::setTotalPrice(const std::string& total) {
    mTotalPrice = total;
}

}  // namespace entity