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
#include "mock/employeemgmt/empmgmtdatamock.hpp"
#include "mock/employeemgmt/empmgmtviewmock.hpp"

// code under test
#include <domain/employeemgmt/employeecontroller.hpp>


// Gmock
using testing::_;
using testing::Return;

namespace domain {
namespace empmgmt {
namespace test {

class TestEmployeeManagement : public testing::Test {
 public:
    TestEmployeeManagement() : empmgmtController(dpMock, viewMock) {
        // Empty for now
    }

    ~TestEmployeeManagement() = default;
    void SetUp() override {}
    void TearDown() override {}

    std::shared_ptr<EmployeeMgmtDataMock> dpMock  = std::make_shared<EmployeeMgmtDataMock>();
    std::shared_ptr<EmployeeMgmtViewMock> viewMock = std::make_shared<EmployeeMgmtViewMock>();
    EmployeeMgmtController empmgmtController;
};

TEST_F(TestEmployeeManagement, TestGetEmployeeList) {
    // Fake that there is at least one employee data on record
    EXPECT_CALL(*dpMock, getEmployees())
        .WillOnce(Return(std::vector<entity::Employee>{entity::Employee()}));
    // The list should not be empty
    ASSERT_NE(empmgmtController.list().size(), 0);
}

TEST_F(TestEmployeeManagement, TestGetEmployeeListWithViewNotInitialized) {
    EmployeeMgmtController dummyController(dpMock, nullptr);
    ASSERT_TRUE(dummyController.list().empty());
}

TEST_F(TestEmployeeManagement, TestGetEmployeeListWithDataNotInitialized) {
    EmployeeMgmtController dummyController(nullptr, viewMock);
    EXPECT_CALL(*viewMock, showDataNotReadyScreen());
    ASSERT_TRUE(dummyController.list().empty());
}

TEST_F(TestEmployeeManagement, TestGetEmployeeData) {
    const std::string requestedID = "1234";
    // Fake that the employee data is saved on record
    EXPECT_CALL(*dpMock, getEmployees())
        .WillOnce(Return(
            std::vector<entity::Employee>{
                entity::Employee(requestedID, "", "", "", "", "", "", "", true)
                }));
    // Cache the list
    empmgmtController.list();
    // Should return a valid employee data (valid EmployeeID)
    ASSERT_FALSE(empmgmtController.get(requestedID).employeeID().empty());
}

TEST_F(TestEmployeeManagement, TestGetEmployeeDataNotFound) {
    const std::string requestedID = "1234";
    const std::string storedEmployeeID = "5678";
    // Fake that we only have an employee with ID 5678
    EXPECT_CALL(*dpMock, getEmployees())
        .WillOnce(Return(
            std::vector<entity::Employee>{
                entity::Employee(storedEmployeeID, "", "", "", "", "", "", "", true)
                }));
    // Cache the list
    empmgmtController.list();
    // Should return an empty employee data (empty EmployeeID)
    ASSERT_TRUE(empmgmtController.get(requestedID).employeeID().empty());
}

TEST_F(TestEmployeeManagement, TestRemoveEmployee) {
    const std::string requestedID = "1234";
    // Fake that the employee data is saved on record
    EXPECT_CALL(*dpMock, getEmployees())
        .WillOnce(Return(
            std::vector<entity::Employee>{
                entity::Employee(requestedID, "", "", "", "", "", "", "", true)
                }));
    // Cache the list
    empmgmtController.list();
    EXPECT_CALL(*viewMock, showSuccessfullyRemoved(_));
    // Should be successful
    ASSERT_EQ(empmgmtController.remove(requestedID), USERSMGMTSTATUS::SUCCESS);
    // The user ID should also be removed from the cachelist
    ASSERT_TRUE(empmgmtController.get(requestedID).employeeID().empty());
}

TEST_F(TestEmployeeManagement, TestRemoveEmployeeNotFound) {
    const std::string requestedID = "1234";
    const std::string storedEmployeeID = "5678";
    // Fake that we only have an employee with ID 5678
    EXPECT_CALL(*dpMock, getEmployees())
        .WillOnce(Return(
            std::vector<entity::Employee>{
                entity::Employee(storedEmployeeID, "", "", "", "", "", "", "", true)
                }));
    // Cache the list
    empmgmtController.list();
    ASSERT_EQ(empmgmtController.remove(requestedID), USERSMGMTSTATUS::NOT_FOUND);
}

TEST_F(TestEmployeeManagement, TestRemoveEmployeeWithViewNotInitialized) {
    EmployeeMgmtController dummyController(dpMock, nullptr);
    ASSERT_EQ(dummyController.remove("1234"), USERSMGMTSTATUS::UNINITIALIZED);
}

TEST_F(TestEmployeeManagement, TestRemoveEmployeeWithDataNotInitialized) {
    EmployeeMgmtController dummyController(nullptr, viewMock);
    EXPECT_CALL(*viewMock, showDataNotReadyScreen());
    ASSERT_EQ(dummyController.remove("1234"), USERSMGMTSTATUS::UNINITIALIZED);
}

}  // namespace test
}  // namespace empmgmt
}  // namespace domain
