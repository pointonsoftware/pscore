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
#include "accountingcontroller.hpp"
#include <memory>
#include <logger/loghelper.hpp>

namespace domain {
namespace accounting {

AccountingController::AccountingController(const AccountingDataPtr& data,
                                           const AccountingViewPtr& view)
                                           : BaseController(data, view) {
    mCachedList.setEntityKeyFn(&entity::Sale::ID);
}

std::vector<GraphReport> AccountingController::getCategorySales() {
    LOG_DEBUG("Retrieving category sales");
    return {};
}

std::vector<GraphReport> AccountingController::getTodaySalesReport() {
    LOG_DEBUG("Retrieving today's sales");
    return {};
}

std::vector<entity::Sale> AccountingController::getSales(Period period) {
    LOG_DEBUG("Retrieving %c sales", static_cast<char>(period));
    return {};
}

std::vector<entity::Sale> AccountingController::getCustomPeriodSales(const std::string& startDate,
                                                                     const std::string& endDate) {
    LOG_DEBUG("Retrieving sales from %s to %s", startDate.c_str(), endDate.c_str());
    return mDataProvider->getSales(startDate, endDate);
}

std::vector<entity::SaleItem>
AccountingController::getSaleDetails(const std::string& transactionID) {
    LOG_DEBUG("Retrieving details of transaction ID %s", transactionID.c_str());
    return {};
}

AccountingControllerPtr createAccountingModule(const AccountingDataPtr& data,
                                               const AccountingViewPtr& view) {
    return std::make_unique<AccountingController>(data, view);
}

}  // namespace accounting
}  // namespace domain
