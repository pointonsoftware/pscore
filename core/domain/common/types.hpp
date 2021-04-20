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
#ifndef CORE_DOMAIN_COMMON_TYPES_HPP_
#define CORE_DOMAIN_COMMON_TYPES_HPP_
#include <string>
#include <vector>

namespace domain {

enum class API_STATUS {
    SUCCESS       = 0x00,
    FAILED        = 0x01,
    UNINITIALIZED = 0x02,
    NOT_FOUND     = 0x03
};

// Types for accounting domain
namespace accounting {

struct TodaySalesSummary {
    uint8_t targetDiffPercentage;  // (currentSale/targetSale) * 100
    unsigned int totalSales;
    unsigned int transactionCount;
};

struct GraphReport {
    std::string key;
    std::string value;
};

struct DailyRevenueComparison {
    std::vector<GraphReport> yesterday;
    std::vector<GraphReport> today;
};

struct MonthStatusReport {
    std::vector<GraphReport> revenue;
    std::vector<GraphReport> cost;
    std::vector<GraphReport> profit;
    std::vector<GraphReport> expense;
};

struct ProductCategoryReport {
  std::string category;
  std::vector<GraphReport> productsCount;  // products remaining  under the category per day
};

enum class Period : char {
    YESTERDAY,
    TODAY,
    THIS_WEEK,
    THIS_MONTH,
    THIS_YEAR
};

}  // namespace accounting
}  // namespace domain
#endif  // CORE_DOMAIN_COMMON_TYPES_HPP_