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
#ifndef CORE_DOMAIN_ACCOUNTING_ACCOUNTINGCONTROLLER_HPP_
#define CORE_DOMAIN_ACCOUNTING_ACCOUNTINGCONTROLLER_HPP_
#include <string>
#include <vector>
#include "interface/accountingiface.hpp"
#include <domain/common/basecontroller.hpp>
#include <entity/sale.hpp>

namespace domain {
namespace accounting {

class AccountingController : public AccountingControlInterface,
                             public BaseController<AccountingDataInterface,
                                                   AccountingViewInterface,
                                                   entity::Sale>  {
 public:
    explicit AccountingController(const AccountingDataPtr& data,
                                  const AccountingViewPtr& view);
    ~AccountingController() = default;

    GraphReport getCategorySales() override;
    GraphReport getTodaySalesReport() override;
    std::vector<entity::Sale> getSales(Period period) override;
    std::vector<entity::Sale> getCustomPeriodSales(const std::string& startDate,
                                                   const std::string& endDate) override;
    std::vector<entity::SaleItem> getSaleDetails(const std::string& transactionID) override;

 private:
    bool isDateTimeRangeValid(const std::string& startDate, const std::string& endDate);
    std::string getTotalSaleByTime(const std::string& time,
                                   const std::vector<entity::Sale>& sales);
};

}  // namespace accounting
}  // namespace domain

#endif  // CORE_DOMAIN_ACCOUNTING_ACCOUNTINGCONTROLLER_HPP_