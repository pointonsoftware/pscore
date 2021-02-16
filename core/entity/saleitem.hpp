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
#ifndef CORE_ENTITY_SALEITEM_HPP_
#define CORE_ENTITY_SALEITEM_HPP_

#include <string>

namespace entity {

// Fields
constexpr char FIELD_SLINAME[] = "Sale.Item.Name";
constexpr char FIELD_SLIUPRC[] = "Sale.Item.Unit.Price";
constexpr char FIELD_SLIQTY[]  = "Sale.Item.Quantity";
constexpr char FIELD_SLITPRC[] = "Sale.Item.Total.Price";

class SaleItem {
 public:
    SaleItem(const std::string& saleID,
             const std::string& productID,
             const std::string& productName,
             const std::string& unitPrice,
             const std::string& quantity,
             const std::string& salePrice);
    SaleItem() = default;
    ~SaleItem() = default;

    // Getters
    std::string saleID() const;
    std::string productID() const;
    std::string productName() const;
    std::string unitPrice() const;
    std::string quantity() const;
    std::string totalPrice() const;

    // Setters
    void setSaleID(const std::string& id);
    void setProductID(const std::string& id);
    void setProductName(const std::string& name);
    void setUnitPrice(const std::string& unitPrice);
    void setQuantity(const std::string& qty);
    void setTotalPrice(const std::string& total);

 private:
    std::string mSaleID;
    std::string mProductID;
    std::string mProductName;
    std::string mUnitPrice;
    std::string mQuantity;
    std::string mTotalPrice;
};

}  // namespace entity
#endif  // CORE_ENTITY_SALEITEM_HPP_