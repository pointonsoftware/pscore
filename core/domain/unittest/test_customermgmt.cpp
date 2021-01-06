/**************************************************************************************************
*                                            PSCORE                                               *
*                               Copyright (C) 2020 Pointon Software                               *
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
#include <entity/customer.hpp>

// mocks
#include "mock/customermgmt/customermgmtdatamock.hpp"
#include "mock/customermgmt/customermgmtviewmock.hpp"

// code under test
#include <domain/customermgmt/customermgmtcontroller.hpp>

// Gmock
using testing::_;
using testing::Matcher;
using testing::Return;

namespace domain {
namespace customermgmt {
namespace test {

class TestCustomerMgmt : public testing::Test {
 public:
    TestCustomerMgmt() : controller(dpMock, viewMock) {
        // Empty for now
    }
    ~TestCustomerMgmt() = default;
    void SetUp() {}
    void TearDown() {}

    std::shared_ptr<CustomerManagementDataMock> dpMock
                    = std::make_shared<CustomerManagementDataMock>();
    std::shared_ptr<CustomerManagementViewMock> viewMock
                    = std::make_shared<CustomerManagementViewMock>();
    CustomerManagementController controller;
};

TEST_F(TestCustomerMgmt, TestGetCustomersList) {
    // Fake that there is at least one customer data on record
    EXPECT_CALL(*dpMock, getCustomers())
        .WillOnce(Return(std::vector<entity::Customer>{entity::Customer()}));
    // The list should not be empty
    ASSERT_FALSE(controller.list().empty());
}

TEST_F(TestCustomerMgmt, TestGetCustomersListEmpty) {
    // Fake that there is no customer data on record
    EXPECT_CALL(*dpMock, getCustomers())
        .WillOnce(Return(std::vector<entity::Customer>{}));
    EXPECT_CALL(*viewMock, showListIsEmptyPopup());
    // The list should be empty
    ASSERT_TRUE(controller.list().empty());
}

}  // namespace test
}  // namespace customermgmt
}  // namespace domain
