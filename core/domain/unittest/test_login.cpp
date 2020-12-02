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
#include <entity/user.hpp>

// mocks
#include "mock/login/logindatamock.hpp"
#include "mock/login/loginviewmock.hpp"

// code under test
#include <domain/userlogin/logincontroller.hpp>


// Gmock
using testing::_;
using testing::Return;

namespace domain {
namespace login {
namespace test {

class TestLogin : public testing::Test {
 public:
    TestLogin() : loginController(dpMock, viewMock) {
        // Empty for now
    }

    ~TestLogin() = default;
    void SetUp() {}
    void TearDown() {}

    std::shared_ptr<LoginDataMock> dpMock  = std::make_shared<LoginDataMock>();
    std::shared_ptr<LoginViewMock> viewMock = std::make_shared<LoginViewMock>();
    LoginController loginController;
    const uint8_t PIN_SIZE = 4;
};

TEST_F(TestLogin, LoginShouldSucceed) {
    const std::string dummyPin = "1234";
    const std::string dummyUID = "JDOE123";
    // Calls findUser
    EXPECT_CALL(*dpMock, findUserByPin(dummyPin))
            .WillOnce(Return(
                entity::User(dummyUID, "Manager", dummyPin, "DummyEmployeeID")));
    // Returns the userID
    ASSERT_EQ(loginController.loginWithPIN(dummyPin), dummyUID);
}

TEST_F(TestLogin, LoginUserNotFound) {
    const std::string dummyPin = "1234";
    // Calls findUser - fake that user was not found
    EXPECT_CALL(*dpMock, findUserByPin(_))
            .WillOnce(Return(
                entity::User("", "", "", "")));
    // Calls showInvalidPINScreen
    EXPECT_CALL(*viewMock, showUserNotFoundScreen());
    // Returns empty
    ASSERT_EQ(loginController.loginWithPIN(dummyPin), "");
}

TEST_F(TestLogin, LoginWithEmptyPIN) {
    // Calls showInvalidPINScreen
    EXPECT_CALL(*viewMock, showInvalidPINScreen());
    // Returns empty
    ASSERT_EQ(loginController.loginWithPIN(""), "");
}

TEST_F(TestLogin, LoginWithNonNumericPIN) {
    // Calls showInvalidPINScreen
    EXPECT_CALL(*viewMock, showInvalidPINScreen());
    // Returns empty
    ASSERT_EQ(loginController.loginWithPIN("abcd"), "");
}

TEST_F(TestLogin, LoginWithFewCharacterPIN) {
    std::string dummyPIN;
    const unsigned int dummyPinSize = PIN_SIZE - 1;
    for (unsigned int i = 0; i < dummyPinSize; ++i) {
        dummyPIN.append("1");
    }
    // Calls showInvalidPINScreen
    EXPECT_CALL(*viewMock, showInvalidPINScreen());
    // Returns empty
    ASSERT_EQ(loginController.loginWithPIN(dummyPIN), "");
}

TEST_F(TestLogin, LoginWithTooManyCharacterPIN) {
    std::string dummyPIN;
    const unsigned int dummyPinSize = PIN_SIZE + 1;
    for (unsigned int i = 0; i < dummyPinSize; ++i) {
        dummyPIN.append("1");
    }
    // Calls showInvalidPINScreen
    EXPECT_CALL(*viewMock, showInvalidPINScreen());
    // Returns empty
    ASSERT_EQ(loginController.loginWithPIN(dummyPIN), "");
}

TEST_F(TestLogin, LoginWithViewNotInitialized) {
    LoginController dummyController(dpMock, nullptr);
    // Returns empty
    ASSERT_EQ(dummyController.loginWithPIN("1234"), "");
}

TEST_F(TestLogin, LoginWithDataProviderNotInitialized) {
    LoginController dummyController(nullptr, viewMock);
    // Calls showDataNotReadyScreen
    EXPECT_CALL(*viewMock, showDataNotReadyScreen());
    // Returns empty
    ASSERT_EQ(dummyController.loginWithPIN("1234"), "");
}

}  // namespace test
}  // namespace login
}  // namespace domain
