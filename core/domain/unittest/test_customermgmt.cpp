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
    // Helper function
    entity::Customer makeValidCustomer(const std::string& id = "") const {
        entity::Customer temp(id, "John", "", "Doe", "", "M");
        temp.setAddress({"DummyL1", "DummyL2", "DummyTown", "DummyProv", ""});
        temp.addPersonalId("Driver's License", "PC13-72021-20");
        return temp;
    }

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

TEST_F(TestCustomerMgmt, TestGetCustomerData) {
    const std::string requestedID = "CMAA95TZ45";
    // Fake that the customer data is saved on record
    EXPECT_CALL(*dpMock, getCustomers())
        .WillOnce(Return(
            std::vector<entity::Customer>{
                entity::Customer(requestedID, "DummyFName", "DummyMName", "DummyLName",
                "DummyBDate", "DummyGender")}));
    // Cache the list
    controller.list();
    // Should return a valid customer data (valid ID)
    ASSERT_FALSE(controller.get(requestedID).ID().empty());
}

TEST_F(TestCustomerMgmt, TestGetCustomerDataNotFound) {
    const std::string requestedID = "CMAA95TZ45";
    const std::string storedCustomer = "CMJB73YN64";
    // Fake that we only have a customer with barcode CMJB73YN64
    EXPECT_CALL(*dpMock, getCustomers())
        .WillOnce(Return(
            std::vector<entity::Customer>{
                entity::Customer(storedCustomer, "DummyFName", "DummyMName", "DummyLName",
                                "DummyBDate", "DummyGender")}));
    // Cache the list
    controller.list();
    // Should return a valid customer data (valid ID)
    ASSERT_TRUE(controller.get(requestedID).ID().empty());
}

TEST_F(TestCustomerMgmt, TestSaveWithNullValidationContainer) {
    ASSERT_EQ(controller.save(entity::Customer(), nullptr),
              CUSTOMERMGMTAPISTATUS::UNINITIALIZED);
}

TEST_F(TestCustomerMgmt, TestSaveWithEmptyCustomerData) {
    std::map<std::string, std::string> dummyValidationContainer;
    ASSERT_EQ(controller.save(entity::Customer(), &dummyValidationContainer),
              CUSTOMERMGMTAPISTATUS::FAILED);
    // Validation result must not be empty
    ASSERT_FALSE(dummyValidationContainer.empty());
}

TEST_F(TestCustomerMgmt, TestCreateCustomer) {
    std::map<std::string, std::string> dummyValidationContainer;
    // DP create must be called
    EXPECT_CALL(*dpMock, create(Matcher<const entity::Customer&>(_)));
    // Should be successful
    ASSERT_EQ(controller.save(makeValidCustomer(), &dummyValidationContainer),
              CUSTOMERMGMTAPISTATUS::SUCCESS);
    // Validation result should be empty
    ASSERT_TRUE(dummyValidationContainer.empty());
}

TEST_F(TestCustomerMgmt, TestCreateCustomerWithInvalidAddress) {
    std::map<std::string, std::string> dummyValidationContainer;
    entity::Customer dummy("", "John", "", "Doe", "", "M");
    dummy.setAddress({"DummyL1", "DummyL2", "", ""});
    // Should fail
    ASSERT_EQ(controller.save(dummy, &dummyValidationContainer),
              CUSTOMERMGMTAPISTATUS::FAILED);
    // Validation result must not be empty
    ASSERT_FALSE(dummyValidationContainer.empty());
}

TEST_F(TestCustomerMgmt, TestCreateCustomerWithInvalidPhone) {
    std::map<std::string, std::string> dummyValidationContainer;
    entity::Customer dummy("", "John", "", "Doe", "", "M");
    dummy.setAddress({"DummyL1", "DummyL2", "DummyTown", "DummyProv", "ZIP"});
    // Invalid size and characters
    dummy.setPhoneNumbers("12312312", "aaaaa");
    // Should fail
    ASSERT_EQ(controller.save(dummy, &dummyValidationContainer),
              CUSTOMERMGMTAPISTATUS::FAILED);
    // Validation result must not be empty
    ASSERT_FALSE(dummyValidationContainer.empty());
}

TEST_F(TestCustomerMgmt, TestUpdateCustomerData) {
    std::map<std::string, std::string> dummyValidationContainer;
    const std::string requestedID = "CMAA95TZ45";
    // Fake that the customer data is saved on record
    EXPECT_CALL(*dpMock, getCustomers())
        .WillOnce(Return(
            std::vector<entity::Customer>{
                entity::Customer(requestedID, "DummyFName", "DummyMName", "DummyLName",
                "DummyBDate", "DummyGender")}));
    // Cache the list
    controller.list();

    // DP update must be called
    EXPECT_CALL(*dpMock, update(Matcher<const entity::Customer&>(_)));
    // Should be successful
    ASSERT_EQ(controller.save(makeValidCustomer(requestedID), &dummyValidationContainer),
              CUSTOMERMGMTAPISTATUS::SUCCESS);
    // Validation result should be empty
    ASSERT_TRUE(dummyValidationContainer.empty());
}

TEST_F(TestCustomerMgmt, TestRemoveCustomer) {
    const std::string requestedID = "CMAA95TZ45";
    // Fake that the customer data is saved on record
    EXPECT_CALL(*dpMock, getCustomers())
        .WillOnce(Return(
            std::vector<entity::Customer>{
                entity::Customer(requestedID, "DummyFName", "DummyMName", "DummyLName",
                "DummyBDate", "DummyGender")}));
    // Cache the list
    controller.list();
    EXPECT_CALL(*viewMock, showSuccessfullyRemoved(_));
    EXPECT_CALL(*dpMock, remove(requestedID));
    // Should be successful
    ASSERT_EQ(controller.remove(requestedID), CUSTOMERMGMTAPISTATUS::SUCCESS);
    // The customer data should also be removed from the cachelist
    ASSERT_TRUE(controller.get(requestedID).ID().empty());
}

TEST_F(TestCustomerMgmt, TestRemoveCustomerDataNotFound) {
    const std::string requestedID = "CMAA95TZ45";
    const std::string storedCustomer = "CMJB73YN64";
    // Fake that we only have a customer with barcode CMJB73YN64
    EXPECT_CALL(*dpMock, getCustomers())
        .WillOnce(Return(
            std::vector<entity::Customer>{
                entity::Customer(storedCustomer, "DummyFName", "DummyMName", "DummyLName",
                                "DummyBDate", "DummyGender")}));
    // Cache the list
    controller.list();
    // Should fail
    ASSERT_EQ(controller.remove(requestedID), CUSTOMERMGMTAPISTATUS::NOT_FOUND);
}

}  // namespace test
}  // namespace customermgmt
}  // namespace domain
