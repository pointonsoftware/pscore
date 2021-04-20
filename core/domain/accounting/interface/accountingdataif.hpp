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
#ifndef CORE_DOMAIN_ACCOUNTING_INTERFACE_ACCOUNTINGDATAIF_HPP_
#define CORE_DOMAIN_ACCOUNTING_INTERFACE_ACCOUNTINGDATAIF_HPP_
#include <string>
#include <vector>
#include <entity/sale.hpp>
#include <entity/saleitem.hpp>

namespace domain {
namespace accounting {

class AccountingDataInterface {
 public:
    AccountingDataInterface() = default;
    virtual ~AccountingDataInterface() = default;
    /*!
     * Returns each sales from the specified period
     * Note: Dates are inclusive
     */
    virtual std::vector<entity::Sale> getSales(const std::string& startDate,
                                               const std::string& endDate) = 0;
    /*!
     * Returns the sale items registered with the transaction ID
     */
    virtual std::vector<entity::SaleItem> getSaleDetails(const std::string& transactionID) = 0;
};

}  // namespace accounting
}  // namespace domain
#endif  // CORE_DOMAIN_ACCOUNTING_INTERFACE_ACCOUNTINGDATAIF_HPP_