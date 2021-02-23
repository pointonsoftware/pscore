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
#include <gtest/gtest.h>

// code under test
#include <domain/sales/salecomputer.hpp>

namespace domain {
namespace sales {
namespace test {

class TestSaleComputer : public testing::Test {
 public:
    TestSaleComputer() = default;
    ~TestSaleComputer() = default;
    void SetUp() {}
    void TearDown() {}

    SaleComputer computer;
    Computation computation;
};

TEST_F(TestSaleComputer, calculateWithSenionCitizenDiscount) {
    computation = computer.compute("1120.00", DISCOUNT_TYPE::SCPWD);
    ASSERT_STREQ(computation.taxableAmount.c_str(), "1000.00");
    ASSERT_STREQ(computation.tax.c_str(), "0.00");
    ASSERT_STREQ(computation.discount.c_str(), "200.00");
    ASSERT_STREQ(computation.amountDue.c_str(), "800.00");
}

TEST_F(TestSaleComputer, calculateWithCouponDiscount) {
    computation = computer.compute("1120.00", DISCOUNT_TYPE::COUPON_1);
    ASSERT_STREQ(computation.taxableAmount.c_str(), "900.00");
    ASSERT_STREQ(computation.tax.c_str(), "108.00");
    ASSERT_STREQ(computation.discount.c_str(), "112.00");
    ASSERT_STREQ(computation.amountDue.c_str(), "1008.00");
}

TEST_F(TestSaleComputer, calculateNormalSale1) {
    computation = computer.compute("1120.00", DISCOUNT_TYPE::NONE);
    ASSERT_STREQ(computation.taxableAmount.c_str(), "1000.00");
    ASSERT_STREQ(computation.tax.c_str(), "120.00");
    ASSERT_STREQ(computation.discount.c_str(), "0.00");
    ASSERT_STREQ(computation.amountDue.c_str(), "1120.00");
}

TEST_F(TestSaleComputer, calculateNormalSale2) {
    computation = computer.compute("56.00", DISCOUNT_TYPE::NONE);
    ASSERT_STREQ(computation.taxableAmount.c_str(), "50.00");
    ASSERT_STREQ(computation.tax.c_str(), "6.00");
    ASSERT_STREQ(computation.discount.c_str(), "0.00");
    ASSERT_STREQ(computation.amountDue.c_str(), "56.00");
}

TEST_F(TestSaleComputer, calculateNormalSale3) {
    computation = computer.compute("336.50", DISCOUNT_TYPE::NONE);
    ASSERT_STREQ(computation.taxableAmount.c_str(), "300.45");
    ASSERT_STREQ(computation.tax.c_str(), "36.05");
    ASSERT_STREQ(computation.discount.c_str(), "0.00");
    ASSERT_STREQ(computation.amountDue.c_str(), "336.50");
}

}  // namespace test
}  // namespace sales
}  // namespace domain
