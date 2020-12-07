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
    const std::string dummyUserId = "JDOE123";
    dashController.setCurrentUserId(dummyUserId);

    // We expect that data provider will perform getUserByID()
    EXPECT_CALL(*dataMock, getUserByID(dummyUserId))
    // Fake that we found a user
        .WillOnce(Return(
        entity::User(dummyUserId, "Manager", "1111", "dummyEmployeeID")));

    entity::User dummyUser = dashController.getCurrentUser();
    // The userID must not be empty
    ASSERT_NE(dummyUser.userID(), "");
}

TEST_F(TestDashboard, GetCurrentUserNotFound) {
    /* Pre-condition
     * According to the API, we should set the current userID
     * before calling getCurrentUserInfo()
    */
    const std::string dummyUserId = "JDOE123";
    dashController.setCurrentUserId(dummyUserId);

    // We expect that data provider will perform getUserByID()
    EXPECT_CALL(*dataMock, getUserByID(dummyUserId))
    // Fake that we did NOT found a user by returning an empty User data
        .WillOnce(Return(entity::User()));
    // We should show an information in the screen
    EXPECT_CALL(*viewMock, showUserNotFound());

    entity::User dummyUser = dashController.getCurrentUser();
    // The userID must be empty
    ASSERT_EQ(dummyUser.userID(), "");
}

TEST_F(TestDashboard, GetCurrentUserWithEmptyUserID) {
    /* This case generally happens because setCurrentUserId() was not
     * used before calling getCurrentUserInfo()
    */

    // We should show an information in the screen
    EXPECT_CALL(*viewMock, showUserNotFound());

    entity::User dummyUser = dashController.getCurrentUser();
    // userID must be empty
    ASSERT_EQ(dummyUser.userID(), "");
}

TEST_F(TestDashboard, GetCurrentUserViewNotInitialized) {
    DashboardController dashboardController(dataMock, nullptr);
    entity::User dummyUser = dashboardController.getCurrentUser();
    // userID must be empty
    ASSERT_EQ(dummyUser.userID(), "");
}

TEST_F(TestDashboard, GetCurrentUserWithDataProviderNotInitialized) {
    DashboardController dashboardController(nullptr, viewMock);

    /* Pre-condition
     * According to the API, we should set the current userID
     * before calling getCurrentUserInfo()
    */
    const std::string dummyUserId = "JDOE123";
    dashboardController.setCurrentUserId(dummyUserId);

    // We should inform the user
    EXPECT_CALL(*viewMock, showDataNotReadyScreen());

    entity::User dummyUser = dashboardController.getCurrentUser();
    // userID must be empty
    ASSERT_EQ(dummyUser.userID(), "");
}



TEST_F(TestDashboard, GetCurrentUserDetailsSuccess) {
    /* Pre-condition
     * According to the API, we should set the current userID
     * before calling getCurrentUserInfo()
    */
    const std::string dummyUserId = "JDOE123";
    const std::string dummyEmployeeId = "202012344";
    dashController.setCurrentUserId(dummyUserId);
    // Fake current user
    entity::User dummyUser(dummyUserId, "Manager", "1111", dummyEmployeeId);

    // We expect that data provider will perform getEmployeeInformation()
    EXPECT_CALL(*dataMock, getEmployeeInformation(dummyEmployeeId))
    // Fake that we found the employee details
        .WillOnce(Return(entity::Employee(dummyEmployeeId,
                         "DummyFname",
                         "DummyMname",
                         "DummyLname",
                         "DummyBdate",
                         "DummyGender",
                         "DummyPosition",
                         "ACTIVE",
                         true)));

    entity::Employee dummyEmployee = dashController.getUserDetails(dummyUser);
    // The employeeID must be the same
    ASSERT_EQ(dummyEmployee.employeeID(), dummyEmployeeId);
    // The user's full name must not be empty
    ASSERT_NE(dummyEmployee.getFullName(), "");
}

TEST_F(TestDashboard, GetCurrentUserDataNotFound) {
    /* Pre-condition
     * According to the API, we should set the current userID
     * before calling getCurrentUserInfo()
    */
    const std::string dummyUserId = "JDOE123";
    const std::string dummyEmployeeId = "202012344";
    dashController.setCurrentUserId(dummyUserId);
    // Fake current user
    entity::User dummyUser(dummyUserId, "Manager", "1111", dummyEmployeeId);

    // We expect that data provider will perform getEmployeeInformation()
    EXPECT_CALL(*dataMock, getEmployeeInformation(dummyEmployeeId))
    // Fake that we did NOT found the employee data by returning an empty data
        .WillOnce(Return(entity::Employee()));
    // We should show an information in the screen
    EXPECT_CALL(*viewMock, showUserNotFound());

    entity::Employee dummyEmployee = dashController.getUserDetails(dummyUser);
    // The employeeID must be empty
    ASSERT_EQ(dummyEmployee.employeeID(), "");
}

TEST_F(TestDashboard, GetCurrentUserDataWithEmptyEmployeeID) {
    // This case generally happens when a user is not an employee
    // Fake current user
    const std::string dummyUserId = "JDOE123";
    // Fake that employeeID is empty (i.e. user is not an employee)
    entity::User dummyUser(dummyUserId, "Manager", "1111", "");

    // We should show an information in the screen
    EXPECT_CALL(*viewMock, showUserNotFound());

    entity::Employee dummyEmployee = dashController.getUserDetails(dummyUser);
    // The employeeID must be empty
    ASSERT_EQ(dummyEmployee.employeeID(), "");
}

TEST_F(TestDashboard, GetCurrentUserDataWithViewNotInitialized) {
    DashboardController dashboardController(dataMock, nullptr);
    entity::User dummyUser;
    entity::Employee dummyEmployee = dashboardController.getUserDetails(dummyUser);
    // employeeID must be empty
    ASSERT_EQ(dummyEmployee.employeeID(), "");
}

TEST_F(TestDashboard, GetCurrentUserDataWithDataProviderNotInitialized) {
    DashboardController dashboardController(nullptr, viewMock);
    const std::string dummyUserId = "JDOE123";
    const std::string dummyEmployeeId = "202012344";
    // Fake current user
    entity::User dummyUser(dummyUserId, "Manager", "1111", dummyEmployeeId);
    // We should inform the user
    EXPECT_CALL(*viewMock, showDataNotReadyScreen());

    entity::Employee dummyEmployee = dashboardController.getUserDetails(dummyUser);
    // employeeID must be empty
    ASSERT_EQ(dummyEmployee.employeeID(), "");
}

}  // namespace test
}  // namespace dashboard
}  // namespace domain
