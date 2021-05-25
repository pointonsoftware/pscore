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
#include <generalutils.hpp>  // general utility
#include <datetime/datetime.hpp>
#include <logger/loghelper.hpp>

namespace domain {
namespace accounting {

// @todo - need to move this to a persistent storage (file or db)
const std::vector<std::string> OPERATING_HOURS = {
    "09:00",
    "10:00",
    "11:00",
    "12:00",
    "13:00",
    "14:00",
    "15:00",
    "16:00",
    "17:00",
    "18:00",
    "19:00",
    "20:00",
};
// used as default hour for date queries
constexpr char ZERO_HOUR[] = "00:00:00";
constexpr char LAST_HOUR[] = "23:59:59";  // end-of-day

AccountingController::AccountingController(const AccountingDataPtr& data,
                                           const AccountingViewPtr& view)
                                           : BaseController(data, view) {
    mCachedList.setEntityKeyFn(&entity::Sale::ID);
}

GraphReport AccountingController::getCategorySales() {
    LOG_DEBUG("Retrieving category sales");
    // @todo: get the list of categories
    // perform getSales(category) for each of the categories
    // e.g. foreach (category : categories)
    //       report.key   = category;
    //       report.value = getTotalSales(category);
    //       vector.emplace(report);
    return {};
}

GraphReport AccountingController::getTodaySalesReport() {
    LOG_DEBUG("Creating today's sales");
    const std::vector<entity::Sale> sales = getSales(Period::TODAY);
    // Get the sales every hour
    GraphReport report;
    // @todo - this algorithm can be improved and iterate the sales vector only once.
    //       - e.g. iterate the sales vector and populate a multi_map<hours, saleItems> container
    for (auto hour : OPERATING_HOURS) {
        GraphMember member;
        member.key = hour;
        member.value = getTotalSaleByTime(hour, sales);
        report.emplace_back(member);
    }
    LOG_INFO("Returning sales report. Size check: %d", report.size());
    return report;
}

std::vector<entity::Sale> AccountingController::getSales(Period period) {
    LOG_DEBUG("Retrieving sales from %d enum", static_cast<char>(period));
    std::string startDate, endDate;
    switch (period) {
        case Period::YESTERDAY:
            break;
        case Period::TODAY:
            startDate = utility::currentDateStr() + " " + ZERO_HOUR;
            endDate   = utility::currentDateStr() + " " + LAST_HOUR;
            break;
        case Period::THIS_WEEK:
            break;
        case Period::THIS_MONTH:
            break;
        case Period::THIS_YEAR:
            break;
    }
    return getCustomPeriodSales(startDate, endDate);
}

std::vector<entity::Sale> AccountingController::getCustomPeriodSales(const std::string& startDate,
                                                                     const std::string& endDate) {
    LOG_DEBUG("Retrieving sales from %s to %s", startDate.c_str(), endDate.c_str());
    if (!isDateTimeRangeValid(startDate, endDate)) {
        LOG_ERROR("Invalid date-time range");
        mView->showInvalidDateTimeRange();
        return {};
    }
    LOG_DEBUG("Sending sales query to the database");
    const std::vector<entity::Sale>& sales = mDataProvider->getSales(startDate, endDate);
    LOG_INFO("Number of sales retrieved from the database: %d", sales.size());
    return sales;
}

std::vector<entity::SaleItem>
AccountingController::getSaleDetails(const std::string& transactionID) {
    LOG_DEBUG("Retrieving details of transaction ID %s", transactionID.c_str());
    return {};
}

bool AccountingController::isDateTimeRangeValid(const std::string& startDate,
                                                const std::string& endDate) {
    utility::DateTimeComparator dateTimeComparator;
    // Start date must be equal or lesser than end date
    return (dateTimeComparator(startDate).compare(endDate)
            == utility::DateTimeComparator::Result::EQUALS) ||
           (dateTimeComparator(startDate).compare(endDate)
            == utility::DateTimeComparator::Result::LESSER_THAN);
}

std::string AccountingController::getTotalSaleByTime(const std::string& time,
                                   const std::vector<entity::Sale>& sales) {
    LOG_DEBUG("Retrieving sales for time: %s", time.c_str());
    double totalSale = 0;
    for (entity::Sale sale : sales) {
        // Ignore the date (10 characters + 1 space) and compare the time
        static const uint8_t IGNORE_SIZE = 11;
        // @todo - improve this algorithm to consider minutes range
        //       - for now we're comparing the "hour" value only
        static const uint8_t HOUR_STR_SIZE = 2;
        const std::string saletimeHour = sale.dateTime().substr(IGNORE_SIZE, HOUR_STR_SIZE);

        if (saletimeHour != time.substr(0, HOUR_STR_SIZE)) {
            continue;
        }
        if (!utility::isDouble(sale.total())) {
            // @todo - this indicates a corrupted db, log this as critical
            LOG_ERROR("Invalid total sale value! Possible indication of a corrupted DB!");
            continue;
        }
        totalSale += utility::toDouble(sale.total());
    }
    return utility::doubleToString(totalSale);
}

bool AccountingController::invalidateSale(const std::string& transactionID) {
    // Stub
    // @todo - add bool isVoid property to sale item in the database
    // @todo - add implementation in the datamanager to toggle that property
    return false;
}

std::vector<entity::Sale> AccountingController::getVoidSales() {
    // Stub
    // @todo - add implementation in the datamanager to return all the sales with isVoid == true
    return {};
}

AccountingControllerPtr createAccountingModule(const AccountingDataPtr& data,
                                               const AccountingViewPtr& view) {
    return std::make_unique<AccountingController>(data, view);
}

}  // namespace accounting
}  // namespace domain
