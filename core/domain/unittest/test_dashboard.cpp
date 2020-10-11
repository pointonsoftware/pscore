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
#include <gmock/gmock.h>
#include <entity/user.hpp>

// mocks
#include "mock/dashboard/dashboarddatamock.hpp"
#include "mock/dashboard/dashboardviewmock.hpp"
// code under test
#include <domain/dashboard/dashboardcontroller.hpp>


// Gmock
using testing::_;
using testing::Return;

namespace domain {
namespace dashboard {
namespace test {

class TestDashboard : public testing::Test {
 public:
    TestDashboard() : dashController(dataMock, viewMock) {
        // Empty for now
    }

    ~TestDashboard() = default;
    void SetUp() {}
    void TearDown() {}
    std::shared_ptr<DashboardDataMock> dataMock = std::make_shared<DashboardDataMock>();
    std::shared_ptr<DashboardViewMock> viewMock = std::make_shared<DashboardViewMock>();
    DashboardController dashController;
};

TEST_F(TestDashboard, GetCurrentUserInfoSuccess) {
    /* Pre-condition
     * According to the API, we should set the current userID
     * before calling getCurrentUserInfo()
    */
    const std::string dummyUserId = "1234";
    dashController.setCurrentUserId(dummyUserId);

    // We expect that data provider will perform getUserByID()
    EXPECT_CALL(*dataMock, getUserByID(dummyUserId))
    // Fake that we found a user
        .WillOnce(Return(
        entity::User("Ben", "H", "Gar", "12/12/1212", "M", dummyUserId, "admin", "1111")));

    entity::User dummyUser = dashController.getCurrentUserInfo();
    // The employeeID must not be empty
    ASSERT_NE(dummyUser.getEmployeeID(), "");
}

TEST_F(TestDashboard, GetCurrentUserNotFound) {
    /* Pre-condition
     * According to the API, we should set the current userID
     * before calling getCurrentUserInfo()
    */
    const std::string dummyUserId = "1234";
    dashController.setCurrentUserId(dummyUserId);

    // We expect that data provider will perform getUserByID()
    EXPECT_CALL(*dataMock, getUserByID(dummyUserId))
    // Fake that we did NOT found a user by returning an empty User data
        .WillOnce(Return(entity::User()));
    // We should show an information in the screen
    EXPECT_CALL(*viewMock, showUserNotFound());

    entity::User dummyUser = dashController.getCurrentUserInfo();
    // The employeeID must be empty
    ASSERT_EQ(dummyUser.getEmployeeID(), "");
}

TEST_F(TestDashboard, GetCurrentUserWithEmptyUserID) {
    /* This case generally happens because setCurrentUserId() was not
     * used before calling getCurrentUserInfo()
    */

    // We should show an information in the screen
    EXPECT_CALL(*viewMock, showUserNotFound());

    entity::User dummyUser = dashController.getCurrentUserInfo();
    // employeeID must be empty
    ASSERT_EQ(dummyUser.getEmployeeID(), "");
}

TEST_F(TestDashboard, GetCurrentUserViewNotInitialized) {
    DashboardController dashboardController(dataMock, nullptr);
    entity::User dummyUser = dashboardController.getCurrentUserInfo();
    // employeeID must be empty
    ASSERT_EQ(dummyUser.getEmployeeID(), "");
}

TEST_F(TestDashboard, GetCurrentUserWithDataProviderNotInitialized) {
    DashboardController dashboardController(nullptr, viewMock);

    /* Pre-condition
     * According to the API, we should set the current userID
     * before calling getCurrentUserInfo()
    */
    const std::string dummyUserId = "1234";
    dashboardController.setCurrentUserId(dummyUserId);

    // We should inform the user
    EXPECT_CALL(*viewMock, showDataNotReadyScreen());

    entity::User dummyUser = dashboardController.getCurrentUserInfo();
    // employeeID must be empty
    ASSERT_EQ(dummyUser.getEmployeeID(), "");
}

}  // namespace test
}  // namespace dashboard
}  // namespace domain
