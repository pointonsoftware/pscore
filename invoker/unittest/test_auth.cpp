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
#include <domain/userlogin/authcontroller.hpp>
#include <entity/user.hpp>

namespace domain {
namespace authentication {
namespace test {

class TestAuth : public testing::Test {
 public:
    TestAuth() : authController(nullptr, nullptr) {
        // empty for now
    }

    ~TestAuth() = default;
    void SetUp() {}
    void TearDown() {}

    domain::authentication::AuthController authController;
};

TEST_F(TestAuth, LoginShouldSucceed) {
    ASSERT_TRUE(authController.loginWithPIN("1234"));
}

TEST_F(TestAuth, LoginWithEmptyPIN) {
    ASSERT_FALSE(authController.loginWithPIN(""));
}

TEST_F(TestAuth, LoginWithNonNumericPIN) {
    ASSERT_FALSE(authController.loginWithPIN("abcd"));
}

TEST_F(TestAuth, LoginWithFewCharacterPIN) {
    std::string dummyPIN;
    const unsigned int dummyPinSize = entity::User::PIN_SIZE - 1;
    std::fill(dummyPIN.begin(),
              dummyPIN.begin() + dummyPinSize, '1');

    ASSERT_FALSE(authController.loginWithPIN(dummyPIN));
}

TEST_F(TestAuth, LoginWithTooManyCharacterPIN) {
    std::string dummyPIN;
    const unsigned int dummyPinSize = entity::User::PIN_SIZE + 1;
    std::fill(dummyPIN.begin(),
              dummyPIN.begin() + dummyPinSize, '1');

    ASSERT_FALSE(authController.loginWithPIN(dummyPIN));
}

}  // namespace test
}  // namespace authentication
}  // namespace domain
