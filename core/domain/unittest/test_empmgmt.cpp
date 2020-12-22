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
using testing::Matcher;
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
    // Helper function
    entity::Employee makeValidEmployee(const std::string& id, bool isUser) const {
        entity::Employee employee(id, "John", "", "Doe", "", "M", "Admin", "ACTIVE", isUser);
        employee.setAddress({"DummyL1", "DummyL2", "DummyTown", "DummyProv", ""});
        employee.addPersonalId("Driver's License", "PC13-72021-20");
        return employee;
    }

    std::shared_ptr<EmployeeMgmtDataMock> dpMock  = std::make_shared<EmployeeMgmtDataMock>();
    std::shared_ptr<EmployeeMgmtViewMock> viewMock = std::make_shared<EmployeeMgmtViewMock>();
    EmployeeMgmtController empmgmtController;
};

TEST_F(TestEmployeeManagement, TestGetEmployeeList) {
    // Fake that there is at least one employee data on record
    EXPECT_CALL(*dpMock, getEmployees())
        .WillOnce(Return(std::vector<entity::Employee>{entity::Employee()}));
    // The list should not be empty
    ASSERT_FALSE(empmgmtController.list().empty());
}

TEST_F(TestEmployeeManagement, TestGetEmployeeListEmpty) {
    // Fake that there is no employee data on record
    EXPECT_CALL(*dpMock, getEmployees())
        .WillOnce(Return(std::vector<entity::Employee>{}));
    EXPECT_CALL(*viewMock, showEmployeesEmptyPopup());
    // The list should be empty
    ASSERT_TRUE(empmgmtController.list().empty());
}

TEST_F(TestEmployeeManagement, TestGetEmployeeListWithViewNotInitialized) {
    try {
        EmployeeMgmtController dummyController(dpMock, nullptr);
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(), std::string("Received a nulltpr argument"));
    }
    catch(...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

TEST_F(TestEmployeeManagement, TestGetEmployeeListWithDataNotInitialized) {
    try {
        EmployeeMgmtController dummyController(nullptr, viewMock);
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(), std::string("Received a nulltpr argument"));
    }
    catch(...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

TEST_F(TestEmployeeManagement, TestGetEmployeeData) {
    const std::string requestedID = "JDOE123";
    // Fake that the employee data is saved on record
    EXPECT_CALL(*dpMock, getEmployees())
        .WillOnce(Return(
            std::vector<entity::Employee>{
                entity::Employee(requestedID, "", "", "", "", "", "", "", true)
                }));
    // Cache the list
    empmgmtController.list();
    // Should return a valid employee data (valid Employee ID)
    ASSERT_FALSE(empmgmtController.get(requestedID).ID().empty());
}

TEST_F(TestEmployeeManagement, TestGetEmployeeDataNotFound) {
    const std::string requestedID = "JDOE123";
    const std::string storedEmployeeID = "PHIP567";
    // Fake that we only have an employee with ID PHIP567
    EXPECT_CALL(*dpMock, getEmployees())
        .WillOnce(Return(
            std::vector<entity::Employee>{
                entity::Employee(storedEmployeeID, "", "", "", "", "", "", "", true)
                }));
    // Cache the list
    empmgmtController.list();
    // Should return an empty employee data (empty Employee ID)
    ASSERT_TRUE(empmgmtController.get(requestedID).ID().empty());
}

TEST_F(TestEmployeeManagement, TestRemoveEmployee) {
    const std::string requestedID = "JDOE123";
    // Fake that the employee data is saved on record
    EXPECT_CALL(*dpMock, getEmployees())
        .WillOnce(Return(
            std::vector<entity::Employee>{
                entity::Employee(requestedID, "", "", "", "", "", "", "", true)
                }));
    // Cache the list
    empmgmtController.list();
    EXPECT_CALL(*viewMock, showSuccessfullyRemoved(_));
    EXPECT_CALL(*dpMock, removeWithID(requestedID));
    // Should be successful
    ASSERT_EQ(empmgmtController.remove(requestedID), EMPLMGMTSTATUS::SUCCESS);
    // The user ID should also be removed from the cachelist
    ASSERT_TRUE(empmgmtController.get(requestedID).ID().empty());
}

TEST_F(TestEmployeeManagement, TestRemoveEmployeeNotFound) {
    const std::string requestedID = "JDOE123";
    const std::string storedEmployeeID = "PHIP567";
    // Fake that we only have an employee with ID PHIP567
    EXPECT_CALL(*dpMock, getEmployees())
        .WillOnce(Return(
            std::vector<entity::Employee>{
                entity::Employee(storedEmployeeID, "", "", "", "", "", "", "", true)
                }));
    // Cache the list
    empmgmtController.list();
    ASSERT_EQ(empmgmtController.remove(requestedID), EMPLMGMTSTATUS::NOT_FOUND);
}

TEST_F(TestEmployeeManagement, TestSaveWithNullValidationContainer) {
    SaveEmployeeData employeeData { entity::Employee(), "", nullptr };
    ASSERT_EQ(empmgmtController.save(employeeData), EMPLMGMTSTATUS::UNINITIALIZED);
}

TEST_F(TestEmployeeManagement, TestSaveWithEmptyEmployeeData) {
    std::map<std::string, std::string> dummyValidationContainer;
    SaveEmployeeData employeeData { entity::Employee(), "", &dummyValidationContainer };
    ASSERT_EQ(empmgmtController.save(employeeData), EMPLMGMTSTATUS::FAILED);
    // Validation result must not be empty
    ASSERT_FALSE(dummyValidationContainer.empty());
}

TEST_F(TestEmployeeManagement, TestSaveSystemUserWithEmptyPin) {
    std::map<std::string, std::string> dummyValidationContainer;
    SaveEmployeeData employeeData {
             makeValidEmployee("", true),
             "",  // PIN is empty
             &dummyValidationContainer
    };
    ASSERT_EQ(empmgmtController.save(employeeData), EMPLMGMTSTATUS::FAILED);
    // Validation result must not be empty
    ASSERT_FALSE(dummyValidationContainer.empty());
}

TEST_F(TestEmployeeManagement, TestCreateEmployee) {
    std::map<std::string, std::string> dummyValidationContainer;
    SaveEmployeeData employeeData {
             makeValidEmployee("JDOE123", false),
             "", &dummyValidationContainer
    };
    // DP create must be called
    EXPECT_CALL(*dpMock, create(Matcher<const entity::Employee&>(_)));
    // Should be successful
    ASSERT_EQ(empmgmtController.save(employeeData), EMPLMGMTSTATUS::SUCCESS);
    // Validation result should be empty
    ASSERT_TRUE(dummyValidationContainer.empty());
}

TEST_F(TestEmployeeManagement, TestCreateUser) {
    std::map<std::string, std::string> dummyValidationContainer;
    SaveEmployeeData employeeData {
             makeValidEmployee("JDOE123", true),
             "1234", &dummyValidationContainer
    };

    // DP create must be called
    EXPECT_CALL(*dpMock, create(Matcher<const entity::User&>(_)));
    // Must display the ID to the user
    EXPECT_CALL(*viewMock, showUserSuccessfullyCreated(_, _));

    // Should be successful
    ASSERT_EQ(empmgmtController.save(employeeData), EMPLMGMTSTATUS::SUCCESS);
    // Validation result should be empty
    ASSERT_TRUE(dummyValidationContainer.empty());
}

TEST_F(TestEmployeeManagement, TestUpdateEmployee) {
    std::map<std::string, std::string> dummyValidationContainer;
    const std::string requestedID = "JDOE123";
    SaveEmployeeData employeeData {
             makeValidEmployee(requestedID, false),
             "", &dummyValidationContainer
    };

    // Pre-condition - cache the user data first
    EXPECT_CALL(*dpMock, getEmployees())
        .WillOnce(Return(
            std::vector<entity::Employee>{
                entity::Employee(requestedID, "", "", "", "", "", "", "", false)
                }));
    empmgmtController.list();

    // DP update must be called
    EXPECT_CALL(*dpMock, update(Matcher<const entity::Employee&>(_)));
    // Should be successful
    ASSERT_EQ(empmgmtController.save(employeeData), EMPLMGMTSTATUS::SUCCESS);
    // Validation result should be empty
    ASSERT_TRUE(dummyValidationContainer.empty());
}

TEST_F(TestEmployeeManagement, TestUpdateUser) {
    std::map<std::string, std::string> dummyValidationContainer;
    const std::string requestedID = "JDOE123";
    SaveEmployeeData employeeData {
             makeValidEmployee(requestedID, true),
             "1234", &dummyValidationContainer
    };

    // Pre-condition - cache the user data first
    EXPECT_CALL(*dpMock, getEmployees())
        .WillOnce(Return(
            std::vector<entity::Employee>{
                entity::Employee(requestedID, "", "", "", "", "", "", "", true)
                }));
    empmgmtController.list();

    // DP update must be called
    EXPECT_CALL(*dpMock, update(Matcher<const entity::User&>(_)));
    // Should be successful
    ASSERT_EQ(empmgmtController.save(employeeData), EMPLMGMTSTATUS::SUCCESS);
    // Validation result should be empty
    ASSERT_TRUE(dummyValidationContainer.empty());
}
}  // namespace test
}  // namespace empmgmt
}  // namespace domain
