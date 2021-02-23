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

Computation SaleComputer::compute(const std::string& totalSale, DISCOUNT_TYPE dsc) {
    Computation computation;
    const double totalSaleValue = utility::toDouble(totalSale);
    double taxableAmount = 0, tax = 0, discount = 0, amountDue = 0;
    /*!
     * Note:
     * - For the computations, it assumed that TAX has already been applied per item
     * - Hence, the tax calculation will be taken from the totalSale
    */
    switch (dsc) {
        case DISCOUNT_TYPE::SCPWD:
            // Extract subtotal (i.e. total sale - 12% tax)
            taxableAmount = totalSaleValue / (1 + VAT);
            // SCs and PWDs don't have tax
            tax = 0;
            {
                const double subtotal = taxableAmount;
                // Get the 20% discount from the subtotal
                discount = subtotal * SCPWD_DISCOUNT;
                // Calculate due
                amountDue = subtotal - discount;
            }
            break;
        case DISCOUNT_TYPE::COUPON_1:
        case DISCOUNT_TYPE::COUPON_2:
            // Apply the discount first
            discount = totalSaleValue * COUPON_DISCOUNT;
            {
                const double discountedAmount = totalSaleValue - discount;
                // Calculate subtotal
                taxableAmount = discountedAmount / (1 + VAT);
                // Tax is extracted from amountDue
                tax = discountedAmount - taxableAmount;
            }
            amountDue = taxableAmount + tax;
            break;
        case DISCOUNT_TYPE::NONE:
            taxableAmount = totalSaleValue / (1 + VAT);
            // Tax is extracted from the total sale value
            tax = totalSaleValue - taxableAmount;
            discount = 0;
            amountDue = taxableAmount + tax;
            break;
        default:
            // All values are zero by default
            break;
    }
    computation.taxableAmount = utility::toString(taxableAmount);
    computation.tax = utility::toString(tax);
    computation.discount = utility::toString(discount);
    computation.amountDue = utility::toString(amountDue);
    return computation;
}

}  // namespace sales
}  // namespace domain