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

TEST_F(TestAccounting, ShouldSucceed) {
    SUCCEED();
}

}  // namespace test
}  // namespace accounting
}  // namespace domain
