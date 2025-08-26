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
#ifndef CORE_ENTITY_SALE_HPP_
#define CORE_ENTITY_SALE_HPP_

#include <string>
#include <vector>
#include "saleitem.hpp"

namespace entity {

/*! Sample Subtotal, TaxableAmount and VAT usage
 *
 * Subtotal      => 1120.00
 * TaxableAmount => 1000.00
 * VAT           => 120.00
 *
 * Note: This is applicable only to stores where TAX is pre-added to the item's diplay price
 */

// Fields
constexpr char FIELD_SALEID[] = "Sale.ID";
constexpr char FIELD_SLTIME[] = "Sale.Timestamp";
constexpr char FIELD_SLITEMS[] = "Sale.Items";
constexpr char FIELD_SLSBTTL[] = "Sale.Subtotal";
constexpr char FIELD_SLTAXAMT[] = "Sale.TaxableAmount";
constexpr char FIELD_SLVAT[] = "Sale.VAT";
constexpr char FIELD_SLDSCT[] = "Sale.Discount";
constexpr char FIELD_SLTOTAL[] = "Sale.Total";
constexpr char FIELD_SLAMTPD[] = "Sale.Paid";
constexpr char FIELD_SLPTYPE[] = "Sale.Payment.Type";
constexpr char FIELD_SLCHNG[] = "Sale.Change";
constexpr char FIELD_SLCSID[] = "Sale.CashierID";
constexpr char FIELD_SLCTID[] = "Sale.CustomerID";

class Sale {
 public:
    Sale(const std::string& saleID,
         const std::string& dateTime,
         const std::vector<SaleItem>& items,
         const std::string& subtotal,
         const std::string& taxableAmount,
         const std::string& vat,
         const std::string& discount,
         const std::string& total,
         const std::string& amountPaid,
         const std::string& paymentType,
         const std::string& change,
         const std::string& cashierID,
         const std::string& customerID);
    Sale() = default;
    ~Sale() = default;

    // Getters
    const std::string& ID() const;
    const std::string& dateTime() const;
    const std::vector<SaleItem>& items() const;
    const std::string& subtotal() const;
    const std::string& taxableAmount() const;
    const std::string& vat() const;
    const std::string& discount() const;
    const std::string& total() const;
    const std::string& amountPaid() const;
    const std::string& paymentType() const;
    const std::string& change() const;
    const std::string& cashierID() const;
    const std::string& customerID() const;

    // Setters
    void setDateTime(const std::string& dateTime);
    void setItems(const std::vector<SaleItem>& items);
    void addItem(const SaleItem& item);
    void setSubtotal(const std::string& subtotal);
    void setTaxableAmount(const std::string& amount);
    void setVAT(const std::string& vat);
    void setDiscount(const std::string& discount);
    void setTotal(const std::string& total);
    void setAmountPaid(const std::string& amount);
    void setPaymentType(const std::string& paymentType);
    void setChange(const std::string& change);
    void setCashierID(const std::string& cashierID);
    void setCustomerID(const std::string& customerID);

 private:
    std::string mID;
    std::string mDateTime;
    std::vector<SaleItem> mItems;
    std::string mSubtotal;
    std::string mTaxableAmount;
    std::string mVAT;
    std::string mDiscount;
    std::string mTotal;
    std::string mAmountPaid;
    std::string mPaymentType;
    std::string mChange;
    std::string mCashierID;
    std::string mCustomerID;
};

}  // namespace entity
#endif  // CORE_ENTITY_SALE_HPP_