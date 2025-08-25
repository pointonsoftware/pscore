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
#ifndef CORE_ENTITY_PRODUCT_HPP_
#define CORE_ENTITY_PRODUCT_HPP_

#include <string>

namespace entity {

// Fields
constexpr char FIELD_BCODE[] = "Product.Barcode";
constexpr char FIELD_SKU[] = "Product.SKU";
constexpr char FIELD_PNAME[] = "Product.Name";
constexpr char FIELD_PDESC[] = "Product.Description";
constexpr char FIELD_CTGR[] = "Product.Category";
constexpr char FIELD_BRAND[] = "Product.Brand";
constexpr char FIELD_UOM[] = "Product.UOM";
constexpr char FIELD_STOCK[] = "Product.Stock";
constexpr char FIELD_PSTATUS[] = "Product.Status";
constexpr char FIELD_OPRICE[] = "Product.Original.Price";
constexpr char FIELD_SPRICE[] = "Product.Sell.Price";
constexpr char FIELD_SPNAME[] = "Product.Supplier.Name";
constexpr char FIELD_SPCODE[] = "Product.Supplier.Code";

class Product {
 public:
    Product(const std::string& barcode,
            const std::string& sku,
            const std::string& name,
            const std::string& description,
            const std::string& category,
            const std::string& brand,
            const std::string& uom,
            const std::string& stock,
            const std::string& status,
            const std::string& originalPrice,
            const std::string& sellPrice,
            const std::string& supplierName,
            const std::string& supplierCode);
    Product() = default;
    ~Product() = default;

    // Getters
    /*!
     * Barcode is used for transaction to make sure the right item is sold
     * to the customer and removed from inventory
    */
    const std::string& barcode() const;
    /*!
     * SKU is used for inventory and sales purposes
     * Used to know the number of products remaining and products sold
    */
    const std::string& sku() const;
    const std::string& name() const;
    const std::string& description() const;
    const std::string& category() const;
    const std::string& brand() const;
    const std::string& uom() const;
    const std::string& stock() const;
    /*!
     * Status is used for knowing the sales and inventory state of the product
     * { High, Active, Reorder, Low Stock }
    */
    const std::string& status() const;
    const std::string& originalPrice() const;
    const std::string& sellPrice() const;
    const std::string& supplierName() const;
    const std::string& supplierCode() const;

    // Setters
    void setBarcode(const std::string& barcode);
    void setSKU(const std::string& sku);
    void setName(const std::string& name);
    void setDescription(const std::string& description);
    void setCategory(const std::string& category);
    void setBrand(const std::string& brand);
    void setUOM(const std::string& uom);
    void setStock(const std::string& stock);
    void setStatus(const std::string& status);
    void setOriginalPrice(const std::string& originalPrice);
    void setSellPrice(const std::string& sellPrice);
    void setSupplierName(const std::string& supplierName);
    void setSupplierCode(const std::string& supplierCode);

    static const uint8_t PRICE_DECIMAL_POINTS = 2;

 private:
    std::string mBarcode;
    std::string mSKU;
    std::string mName;
    std::string mDescription;
    std::string mCategory;
    std::string mBrand;
    std::string mUOM;
    std::string mStock;
    std::string mStatus;
    std::string mOriginalPrice;
    std::string mSellPrice;
    std::string mSupplierName;
    std::string mSupplierCode;
};

}  // namespace entity
#endif  // CORE_ENTITY_PRODUCT_HPP_