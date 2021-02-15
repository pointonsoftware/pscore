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
#include "mock/sales/salesdatamock.hpp"
#include "mock/sales/salesviewmock.hpp"

// code under test
#include <domain/sales/salescontroller.hpp>


// Gmock
using testing::_;
using testing::Return;

namespace domain {
namespace sales {
namespace test {

class TestSales : public testing::Test {
 public:
    TestSales() : controller(dpMock, viewMock) {
        // Empty for now
    }

    ~TestSales() = default;
    void SetUp() {}
    void TearDown() {}

    std::shared_ptr<SalesDataMock> dpMock  = std::make_shared<SalesDataMock>();
    std::shared_ptr<SalesViewMock> viewMock = std::make_shared<SalesViewMock>();
    SalesController controller;
};

TEST_F(TestSales, ShouldSucceed) {
    SUCCEED();
}

}  // namespace test
}  // namespace sales
}  // namespace domain
