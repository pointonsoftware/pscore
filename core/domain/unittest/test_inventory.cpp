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
#include <entity/product.hpp>

// mocks
#include "mock/inventory/inventorydatamock.hpp"
#include "mock/inventory/inventoryviewmock.hpp"

// code under test
#include <domain/inventory/inventorycontroller.hpp>

// Gmock
using testing::_;
using testing::Matcher;
using testing::Return;

namespace domain {
namespace inventory {
namespace test {

class TestInventory : public testing::Test {
 public:
    TestInventory() : inventoryController(dpMock, viewMock),
    validProduct("DUMMY-BARCODE-123", "DUMMY-SKU", "ProductName",
                 "Description", "DummyCategory", "SomeBrand",
                 "SomeMeasurement", "12", "High", "10.00", "12.00",
                 "DummySupplier", "DummySupplierCode") {
        // Empty for now
    }

    ~TestInventory() = default;
    void SetUp() {}
    void TearDown() {}

    std::shared_ptr<InventoryDataMock> dpMock  = std::make_shared<InventoryDataMock>();
    std::shared_ptr<InventoryViewMock> viewMock = std::make_shared<InventoryViewMock>();
    InventoryController inventoryController;
    entity::Product validProduct;
};

TEST_F(TestInventory, TestGetProductsList) {
    // Fake that there is at least one product data on record
    EXPECT_CALL(*dpMock, getProducts())
        .WillOnce(Return(std::vector<entity::Product>{entity::Product()}));
    // The list should not be empty
    ASSERT_FALSE(inventoryController.list().empty());
}

TEST_F(TestInventory, TestGetProductsListEmpty) {
    // Fake that there is no product data on record
    EXPECT_CALL(*dpMock, getProducts())
        .WillOnce(Return(std::vector<entity::Product>{}));
    EXPECT_CALL(*viewMock, showProductsEmptyPopup());
    // The list should be empty
    ASSERT_TRUE(inventoryController.list().empty());
}

TEST_F(TestInventory, TestGetProductData) {
    const std::string requestedBarcode = "124412222020";
    // Fake that the product data is saved on record
    EXPECT_CALL(*dpMock, getProducts())
        .WillOnce(Return(
            std::vector<entity::Product>{
                entity::Product(requestedBarcode, "DUMMY-SKU", "", "", "", "", "", "", "",
                                "", "", "", "")}));
    // Cache the list
    inventoryController.list();
    // Should return a valid product data (valid SKU)
    ASSERT_FALSE(inventoryController.getProduct(requestedBarcode).sku().empty());
}

TEST_F(TestInventory, TestGetProductDataNotFound) {
    const std::string requestedBarcode = "124412222020";
    const std::string storedProduct = "111111999999";
    // Fake that we only have a product with barcode 111111999999
    EXPECT_CALL(*dpMock, getProducts())
        .WillOnce(Return(
            std::vector<entity::Product>{
                entity::Product(storedProduct, "DUMMY-SKU", "", "", "", "", "", "", "",
                                "", "", "", "")}));
    // Cache the list
    inventoryController.list();
    // Should return an empty product data (empty SKU)
    ASSERT_TRUE(inventoryController.getProduct(requestedBarcode).sku().empty());
}

TEST_F(TestInventory, TestRemoveProduct) {
    const std::string requestedBarcode = "124412222020";
    // Fake that the product data is saved on record
    EXPECT_CALL(*dpMock, getProducts())
        .WillOnce(Return(
            std::vector<entity::Product>{
                entity::Product(requestedBarcode, "DUMMY-SKU", "", "", "", "", "", "", "",
                                "", "", "", "")}));
    // Cache the list
    inventoryController.list();
    EXPECT_CALL(*viewMock, showSuccessfullyRemoved(_));
    EXPECT_CALL(*dpMock, removeWithBarcode(requestedBarcode));
    // Should be successful
    ASSERT_EQ(inventoryController.remove(requestedBarcode), INVENTORYAPISTATUS::SUCCESS);
    // The product should also be removed from the cachelist
    ASSERT_TRUE(inventoryController.getProduct(requestedBarcode).sku().empty());
}

TEST_F(TestInventory, TestRemoveProductNotFound) {
    const std::string requestedBarcode = "124412222020";
    const std::string storedProduct = "111111999999";
    // Fake that we only have a product with barcode 111111999999
    EXPECT_CALL(*dpMock, getProducts())
        .WillOnce(Return(
            std::vector<entity::Product>{
                entity::Product(storedProduct, "DUMMY-SKU", "", "", "", "", "", "", "",
                                "", "", "", "")}));
    // Cache the list
    inventoryController.list();
    EXPECT_CALL(*viewMock, showDataNotReadyScreen());
    ASSERT_EQ(inventoryController.remove(requestedBarcode), INVENTORYAPISTATUS::NOT_FOUND);
}

TEST_F(TestInventory, TestSaveWithNullValidationContainer) {
    ASSERT_EQ(inventoryController.save(entity::Product(), nullptr),
              INVENTORYAPISTATUS::UNINITIALIZED);
}

TEST_F(TestInventory, TestSaveWithInvalidProduct) {
    const uint8_t numberOfRequiredFields = 12;
    std::map<std::string, std::string> dummyValidationContainer;
    ASSERT_EQ(inventoryController.save(entity::Product(), &dummyValidationContainer),
              INVENTORYAPISTATUS::FAILED);
    // Validation result must not be empty
    ASSERT_EQ(dummyValidationContainer.size(), numberOfRequiredFields);
}

TEST_F(TestInventory, TestSaveWithInvalidStock) {
    entity::Product dummyProduct("DUMMY-BARCODE-123", "DUMMY-SKU", "ProductName",
                 "Description", "DummyCategory", "SomeBrand",
                 "SomeMeasurement", "-12", "High", "10.00", "12.00",
                 "DummySupplier", "DummySupplierCode");
    std::map<std::string, std::string> dummyValidationContainer;

    ASSERT_EQ(inventoryController.save(dummyProduct, &dummyValidationContainer),
              INVENTORYAPISTATUS::FAILED);
    // Validation result must contain one error
    ASSERT_EQ(dummyValidationContainer.size(), 1);
}

TEST_F(TestInventory, TestSaveWithInvalidPrices) {
    entity::Product dummyProduct("DUMMY-BARCODE-123", "DUMMY-SKU", "ProductName",
                 "Description", "DummyCategory", "SomeBrand",
                 "SomeMeasurement", "12", "High", "10.000", "text.00",
                 "DummySupplier", "DummySupplierCode");
    std::map<std::string, std::string> dummyValidationContainer;
    ASSERT_EQ(inventoryController.save(dummyProduct, &dummyValidationContainer),
              INVENTORYAPISTATUS::FAILED);
    // Validation result must contain two errors
    ASSERT_EQ(dummyValidationContainer.size(), 2);
}

TEST_F(TestInventory, TestSaveWithInvalidSellingPrice) {
    // Fake that selling price is lesser than the original price
    entity::Product dummyProduct("DUMMY-BARCODE-123", "DUMMY-SKU", "ProductName",
                 "Description", "DummyCategory", "SomeBrand",
                 "SomeMeasurement", "12", "High", "10.00", "9.00",
                 "DummySupplier", "DummySupplierCode");
    std::map<std::string, std::string> dummyValidationContainer;
    ASSERT_EQ(inventoryController.save(dummyProduct, &dummyValidationContainer),
              INVENTORYAPISTATUS::FAILED);
    // Validation result must contain one error
    ASSERT_EQ(dummyValidationContainer.size(), 1);
}

TEST_F(TestInventory, TestCreateProduct) {
    std::map<std::string, std::string> dummyValidationContainer;
    ASSERT_EQ(inventoryController.save(validProduct, &dummyValidationContainer),
              INVENTORYAPISTATUS::SUCCESS);
    // Validation result must be empty
    ASSERT_TRUE(dummyValidationContainer.empty());
}

}  // namespace test
}  // namespace inventory
}  // namespace domain
