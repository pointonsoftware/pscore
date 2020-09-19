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
    ASSERT_TRUE(authController.login("123"));
}

TEST_F(TestAuth, DISABLED_LoginShouldFail) {
    ASSERT_FALSE(authController.login("123"));
}

}  // namespace test
}  // namespace authentication
}  // namespace domain