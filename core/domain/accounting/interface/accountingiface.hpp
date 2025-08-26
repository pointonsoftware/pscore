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
#ifndef CORE_DOMAIN_ACCOUNTING_INTERFACE_ACCOUNTINGIFACE_HPP_
#define CORE_DOMAIN_ACCOUNTING_INTERFACE_ACCOUNTINGIFACE_HPP_
#include <memory>
#include <string>
#include <vector>
#include "accountingdataif.hpp"
#include "accountingviewif.hpp"
#include <domain/common/librarycommon.hpp>
#include <domain/common/types.hpp>
#include <entity/sale.hpp>

namespace domain {
namespace accounting {

class AccountingControlInterface {
 public:
    AccountingControlInterface() = default;
    virtual ~AccountingControlInterface() = default;

    /*!
     * Returns sales that can be used for graph reports
     * x = category name, y = category sales this month
     */
    virtual GraphReport getCategorySales() = 0;
    /*!
     * Hourly interval
     */
    virtual GraphReport getTodaySalesReport() = 0;
    /*!
     * Returns each sales
     */
    virtual std::vector<entity::Sale> getSales(Period period) = 0;
    /*!
     * Returns each sales from the specified period
     * Note: Dates are inclusive
     */
    virtual std::vector<entity::Sale> getCustomPeriodSales(const std::string& startDate,
                                                           const std::string& endDate) = 0;
    /*!
     * Returns the sale items registered with the transaction ID
     */
    virtual std::vector<entity::SaleItem> getSaleDetails(const std::string& transactionID) = 0;
    /*!
     * Used to void a sale/transaction
     * Returns true if successful; false otherwise
     */
    virtual bool invalidateSale(const std::string& transactionID) = 0;
    /*!
     * Returns all void sales
     */
    virtual std::vector<entity::Sale> getVoidSales() = 0;
};

typedef std::shared_ptr<AccountingDataInterface> AccountingDataPtr;
typedef std::shared_ptr<AccountingViewInterface> AccountingViewPtr;
typedef std::unique_ptr<AccountingControlInterface> AccountingControllerPtr;

// Lib APIs
CORE_API AccountingControllerPtr createAccountingModule
(const AccountingDataPtr& data, const AccountingViewPtr& view);

}  // namespace accounting
}  // namespace domain
#endif  // CORE_DOMAIN_ACCOUNTING_INTERFACE_ACCOUNTINGIFACE_HPP_