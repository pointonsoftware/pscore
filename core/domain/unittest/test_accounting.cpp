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

// mocks
#include "mock/accounting/accountingdatamock.hpp"
#include "mock/accounting/accountingviewmock.hpp"

// code under test
#include <domain/accounting/accountingcontroller.hpp>

// Gmock
using testing::_;
using testing::Return;

namespace domain {
namespace accounting {
namespace test {

class TestAccounting : public testing::Test {
 public:
    TestAccounting() : controller(dpMock, viewMock) {
        // Empty for now
    }

    ~TestAccounting() = default;
    void SetUp() {}
    void TearDown() {}

    std::shared_ptr<AccountingDataMock> dpMock  = std::make_shared<AccountingDataMock>();
    std::shared_ptr<AccountingViewMock> viewMock = std::make_shared<AccountingViewMock>();
    AccountingController controller;
};

class TestAccountingGetSales : public TestAccounting,
    public ::testing::WithParamInterface<Period> {};

INSTANTIATE_TEST_SUITE_P(
    TestInstantiation, TestAccountingGetSales, testing::Values(
    Period::YESTERDAY,
    Period::TODAY,
    Period::THIS_WEEK,
    Period::THIS_MONTH,
    Period::THIS_YEAR)
    );

TEST_F(TestAccounting, TestGetCategorySales) {
    const std::vector<std::string> fakeCategory = {"Grocery"};
    const std::string fakeSaleID = "100000001";
    const std::vector<entity::Sale> fakeSaleData =
        { entity::Sale{fakeSaleID, "2021-05-16 10:12:20", {}, "",
                       "", "", "", "", "", "", "", "", ""} };
    const std::vector<entity::SaleItem> fakeSaleItem =
        { entity::SaleItem{fakeSaleID, "111", "Chippy", "Grocery",
            "10.00", "10", "100.00"},
          entity::SaleItem{fakeSaleID, "222", "Timbits", "Grocery",
            "5.00", "10", "50.00"} };
    // Fake category data from db
    EXPECT_CALL(*dpMock, getCategories())
            .WillOnce(Return(fakeCategory));
    EXPECT_CALL(*dpMock, getSales(_, _))
            .WillOnce(Return(fakeSaleData));
    // Fake transaction data from db
    EXPECT_CALL(*dpMock, getSaleDetails(fakeSaleID))
            .WillOnce(Return(fakeSaleItem));
    GraphReport expectedReturn = controller.getCategorySales();
    // GraphReport size must be the same as the number of categories in the database
    ASSERT_EQ(expectedReturn.size(), fakeCategory.size());
    // Let's verify the values in the graph report - check index 0 since we only have one category
    ASSERT_EQ(expectedReturn[0].key, "Grocery");
    ASSERT_EQ(expectedReturn[0].value, "150.00");  // must be the total of all items in category
}

TEST_F(TestAccounting, GetCustomPeriodSalesWithInvalidDateRange) {
    const std::string startDate = "2020-01-01 01:01:01";
    // end date is lesser than startdate
    const std::string endDate   = "1990-01-01 01:01:01";
    // Should call a view interface
    EXPECT_CALL(*viewMock, showInvalidDateTimeRange());

    const std::vector<entity::Sale> expectedReturn =
        controller.getCustomPeriodSales(startDate, endDate);
    // Should be empty
    ASSERT_TRUE(expectedReturn.empty());
}

TEST_F(TestAccounting, GetCustomPeriodSalesShouldSucceed) {
    const std::string startDate = "2020-01-01 01:01:01";
    // end date is greater than startdate
    const std::string endDate   = "2021-01-01 01:01:01";
    const std::vector<entity::Sale> fakeData =
        { entity::Sale{"100000001", "2021-05-16 10:12:20", {}, "",
                       "", "", "", "", "", "", "", "", ""} };
    // Should query the database
    EXPECT_CALL(*dpMock, getSales(startDate, endDate))
            .WillOnce(Return(fakeData));
    const std::vector<entity::Sale> sales = controller.getCustomPeriodSales(startDate, endDate);
    // Should not be empty
    ASSERT_FALSE(sales.empty());
}

TEST_F(TestAccounting, GetTodaySalesReportShouldSucceed) {
    const std::vector<entity::Sale> fakeData =
        { entity::Sale{"100000001", "2021-05-16 10:12:20", {}, "",
                       "", "", "", "100.00", "", "", "", "", ""} };
    // Should query the database
    EXPECT_CALL(*dpMock, getSales(_, _))
            .WillOnce(Return(fakeData));

    const GraphReport salesReport = controller.getTodaySalesReport();
    // Should not be empty, verify the contents
    EXPECT_FALSE(salesReport.empty());
    // Verify if the function returns the correct total sales per hour
    const GraphMember member = salesReport.at(1);  // index 1 is the 10:00 hour slot
    ASSERT_STREQ(member.value.c_str(), "100.00");
}

TEST_P(TestAccountingGetSales, GetTodaySalesShouldSucceed) {
    const std::vector<entity::Sale> fakeData =
        { entity::Sale{"100000001", "2021-05-16 10:12:20", {}, "",
                       "", "", "", "", "", "", "", "", ""} };
    // Should query the database
    EXPECT_CALL(*dpMock, getSales(_, _))
            .WillOnce(Return(fakeData));

    const std::vector<entity::Sale> sales = controller.getSales(GetParam());
    // Should not be empty, verify the contents
    ASSERT_FALSE(sales.empty());
}

}  // namespace test
}  // namespace accounting
}  // namespace domain
