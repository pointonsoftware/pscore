/**************************************************************************************************
*                      Copyright (C) Pointon Software - All Rights Reserved                       *
*                                                                                                 *
*             Unauthorized copying of this file via any medium is strictly prohibited             *
*                                  Proprietary and confidential                                   *
*                                                                                                 *
*                   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020                   *
*                                                                                                 *
**************************************************************************************************/
#include <gtest/gtest.h>
#include <controllers/authcontroller.hpp>

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
    bool retValue = authController.login("123");
    ASSERT_TRUE(retValue);
}

TEST_F(TestAuth, DISABLED_LoginShouldFail) {
    bool retValue = authController.login("123");
    ASSERT_FALSE(retValue);
}

}  // namespace test
}  // namespace authentication
}  // namespace domain