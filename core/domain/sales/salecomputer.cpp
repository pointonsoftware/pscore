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
#include "salecomputer.hpp"
#include <general.hpp>

namespace domain {
namespace sales {

constexpr double VAT = 0.12;  // 12%
constexpr double SCPWD_DISCOUNT = 0.20;  // 20%
constexpr double COUPON_DISCOUNT = 0.10;  // 10%

Computation SaleComputer::compute(const std::string& subtotal, DISCOUNT_TYPE dsc) {
    Computation computation;
    computation.amountOfSale = subtotal;
    switch (dsc) {
        case DISCOUNT_TYPE::SCPWD:
        // Calculate sales here
        // Due = Subtotal - (Subtotal * SCPWD_DISCOUNT)
        computation.tax = "0";
        break;
        case DISCOUNT_TYPE::COUPON_1:
        case DISCOUNT_TYPE::COUPON_2:
        // Calculate sales here
        // Subtotal -= (Subtotal * COUPON_DISCOUNT)
        // Due = Subtotal + (Subtotal * VAT)
        break;
        case DISCOUNT_TYPE::NONE:
        // Calculate sales here
        // Due = Subtotal + (Subtotal * VAT)
        computation.discount = "0";
        default:

        break;
    }
    return computation;
}

}  // namespace sales
}  // namespace domain