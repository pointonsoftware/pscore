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
#include "accountingdata.hpp"
#include <storage/stackdb.hpp>

namespace dataprovider {
namespace accounting {

using utility::DateTimeComparator;

std::vector<entity::Sale> AccountingDataProvider::getSales(const std::string& startDate,
                                                           const std::string& endDate) {
    // SELECT Sales
    std::vector<entity::Sale> sales;
    for (const db::SalesTableItem& temp : DATABASE().SELECT_SALES_TABLE()) {
        /*!
         * If temp.date_time < startDate || temp.date_time > endDate ; continue;
        */
        if ((mDateTimeComparator(temp.date_time).compare(startDate)
            == DateTimeComparator::Result::LESSER_THAN) ||
            (mDateTimeComparator(temp.date_time).compare(endDate)
            == DateTimeComparator::Result::GREATER_THAN)) {
            continue;
        }
        const std::vector<entity::SaleItem>& items = getSaleDetails(temp.ID);
        sales.emplace_back(entity::Sale(
            temp.ID,
            temp.date_time,
            items,
            temp.subtotal,
            temp.taxable_amount,
            temp.vat,
            temp.discount,
            temp.total,
            temp.amount_paid,
            temp.payment_type,
            temp.change,
            temp.cashierID,
            temp.customerID));
    }
    return sales;
}

std::vector<entity::SaleItem>
AccountingDataProvider::getSaleDetails(const std::string& transactionID) {
    // SELECT SaleItems
    std::vector<entity::SaleItem> items;
    for (const db::SalesItemTableItem& temp : DATABASE().SELECT_SALES_ITEM_TABLE()) {
        if (temp.saleID != transactionID) {
            continue;
        }
        items.emplace_back(entity::SaleItem(
            temp.saleID,
            temp.productID,
            temp.product_name,
            temp.product_category,
            temp.unit_price,
            temp.quantity,
            temp.total_price));
    }
    return items;
}

std::vector<std::string> AccountingDataProvider::getCategories() {
    std::vector<std::string> categories;
    for (const db::CategoryTableItem& temp : DATABASE().SELECT_CATEGORY_TABLE()) {
        categories.emplace_back(temp.category_name);
    }
    return categories;
}

}  // namespace accounting
}  // namespace dataprovider