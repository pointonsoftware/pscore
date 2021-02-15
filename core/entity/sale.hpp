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

namespace entity {

// Fields
constexpr char FIELD_SALEID[] = "Sale.ID";
constexpr char FIELD_SLTIME[] = "Sale.Timestamp";
constexpr char FIELD_SLITEMS[] = "Sale.Items";
constexpr char FIELD_SLSBTTL[] = "Sale.Subtotal";
constexpr char FIELD_SLTAX[] = "Sale.Tax";
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
         const std::vector<std::string>& items,
         const std::string& subtotal,
         const std::string& tax,
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
    std::string ID() const;
    std::string dateTime() const;
    std::vector<std::string> items() const;
    std::string subtotal() const;
    std::string tax() const;
    std::string discount() const;
    std::string total() const;
    std::string amountPaid() const;
    std::string paymentType() const;
    std::string change() const;
    std::string cashierID() const;
    std::string customerID() const;

    // Setters
    void setDateTime(const std::string& dateTime);
    void setItems(const std::vector<std::string>& items);
    void addItem(const std::string& item);
    void setSubtotal(const std::string& subtotal);
    void setTax(const std::string& tax);
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
    std::vector<std::string> mItems;
    std::string mSubtotal;
    std::string mTax;
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