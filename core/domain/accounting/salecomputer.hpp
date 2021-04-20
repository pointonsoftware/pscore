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
#ifndef CORE_DOMAIN_ACCOUNTING_SALECOMPUTER_HPP_
#define CORE_DOMAIN_ACCOUNTING_SALECOMPUTER_HPP_
#include <string>

namespace domain {
namespace accounting {

enum class DISCOUNT_TYPE {
    NONE,
    SCPWD,
    COUPON_1,
    COUPON_2
};

struct Computation {
    std::string taxableAmount;
    std::string tax;
    std::string discount;
    std::string amountDue;
};

class SaleComputer {
 public:
    SaleComputer() = default;
    ~SaleComputer() = default;
    Computation compute(const std::string& subtotal, DISCOUNT_TYPE dsc = DISCOUNT_TYPE::NONE);
};

}  // namespace accounting
}  // namespace domain

#endif  // CORE_DOMAIN_ACCOUNTING_SALECOMPUTER_HPP_