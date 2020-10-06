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
    TestDashboard() : dashController(viewMock) {
        // Empty for now
    }

    ~TestDashboard() = default;
    void SetUp() {}
    void TearDown() {}
    std::shared_ptr<DashboardViewMock> viewMock = std::make_shared<DashboardViewMock>();
    DashboardController dashController;
};

TEST_F(TestDashboard, DISABLED_GetCurrentUserInfoSuccess) {
    // const std::string dummyPin = "1234";
    // const std::string dummyUID = "11111";
    // // Calls findUser
    // EXPECT_CALL(*dpMock, findUserByPin(dummyPin))
    //     .WillOnce(Return(
    //     entity::User("Ben", "H", "Gar", "12/12/1212", "M", dummyUID, "admin", dummyPin)));
    // // Returns the userID
    // ASSERT_EQ(loginController.loginWithPIN(dummyPin), dummyUID);
}

TEST_F(TestDashboard, DISABLED_GetCurrentUserInvalidUID) {
    const std::string dummyPin = "1234";
    // const std::string dummyUID = "11111";
    // // Calls findUser
    // EXPECT_CALL(*dpMock, findUserByPin(dummyPin))
    //     .WillOnce(Return(
    //     entity::User("Ben", "H", "Gar", "12/12/1212", "M", dummyUID, "admin", dummyPin)));
    // // Returns the userID
    // ASSERT_EQ(loginController.loginWithPIN(dummyPin), dummyUID);
}

TEST_F(TestDashboard, DISABLED_GetCurrentUserNotFound) {
    const std::string dummyPin = "1234";
    // const std::string dummyUID = "11111";
    // // Calls findUser
    // EXPECT_CALL(*dpMock, findUserByPin(dummyPin))
    //     .WillOnce(Return(
    //     entity::User("Ben", "H", "Gar", "12/12/1212", "M", dummyUID, "admin", dummyPin)));
    // // Returns the userID
    // ASSERT_EQ(loginController.loginWithPIN(dummyPin), dummyUID);
}

TEST_F(TestDashboard, DISABLED_GetCurrentUserViewNotInitialized) {
    const std::string dummyPin = "1234";
    // const std::string dummyUID = "11111";
    // // Calls findUser
    // EXPECT_CALL(*dpMock, findUserByPin(dummyPin))
    //     .WillOnce(Return(
    //     entity::User("Ben", "H", "Gar", "12/12/1212", "M", dummyUID, "admin", dummyPin)));
    // // Returns the userID
    // ASSERT_EQ(loginController.loginWithPIN(dummyPin), dummyUID);
}

TEST_F(TestDashboard, DISABLED_GetCurrentUserDpNotInitialized) {
    const std::string dummyPin = "1234";
    // const std::string dummyUID = "11111";
    // // Calls findUser
    // EXPECT_CALL(*dpMock, findUserByPin(dummyPin))
    //     .WillOnce(Return(
    //     entity::User("Ben", "H", "Gar", "12/12/1212", "M", dummyUID, "admin", dummyPin)));
    // // Returns the userID
    // ASSERT_EQ(loginController.loginWithPIN(dummyPin), dummyUID);
}

}  // namespace test
}  // namespace dashboard
}  // namespace domain
