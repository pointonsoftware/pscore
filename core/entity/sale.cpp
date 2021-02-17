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
#include "sale.hpp"
#include <string>

namespace entity {

Sale::Sale(const std::string& saleID,
           const std::string& dateTime,
           const std::vector<SaleItem>& items,
           const std::string& subtotal,
           const std::string& tax,
           const std::string& discount,
           const std::string& total,
           const std::string& amountPaid,
           const std::string& paymentType,
           const std::string& change,
           const std::string& cashierID,
           const std::string& customerID)
           : mID(saleID), mDateTime(dateTime), mItems(items), mSubtotal(subtotal), mTax(tax),
           mDiscount(discount), mTotal(total), mAmountPaid(amountPaid), mPaymentType(paymentType),
           mChange(change), mCashierID(cashierID), mCustomerID(customerID) {
    // Empty for now
}

std::string Sale::ID() const {
    return mID;
}

std::string Sale::dateTime() const {
    return mDateTime;
}

std::vector<SaleItem> Sale::items() const {
    return mItems;
}

std::string Sale::subtotal() const {
    return mSubtotal;
}

std::string Sale::tax() const {
    return mTax;
}

std::string Sale::discount() const {
    return mDiscount;
}

std::string Sale::total() const {
    return mTotal;
}

std::string Sale::amountPaid() const {
    return mAmountPaid;
}

std::string Sale::paymentType() const {
    return mPaymentType;
}

std::string Sale::change() const {
    return mChange;
}

std::string Sale::cashierID() const {
    return mCashierID;
}

std::string Sale::customerID() const {
    return mCustomerID;
}

void Sale::setDateTime(const std::string& dateTime) {
    mDateTime = dateTime;
}

void Sale::setItems(const std::vector<SaleItem>& items) {
    mItems = items;
}

void Sale::addItem(const SaleItem& item) {
    mItems.emplace_back(item);
}

void Sale::setSubtotal(const std::string& subtotal) {
    mSubtotal = subtotal;
}

void Sale::setTax(const std::string& tax) {
    mTax = tax;
}

void Sale::setDiscount(const std::string& discount) {
    mDiscount = discount;
}

void Sale::setTotal(const std::string& total) {
    mTotal = total;
}

void Sale::setAmountPaid(const std::string& amount) {
    mAmountPaid = amount;
}

void Sale::setPaymentType(const std::string& paymentType) {
    mPaymentType = paymentType;
}

void Sale::setChange(const std::string& change) {
    mChange = change;
}

void Sale::setCashierID(const std::string& cashierID) {
    mCashierID = cashierID;
}

void Sale::setCustomerID(const std::string& customerID) {
    mCustomerID = customerID;
}

}  // namespace entity