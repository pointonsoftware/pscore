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
                 "L", "12", "High", "10.00", "12.00",
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

TEST_F(TestInventory, InitWithViewNotInitialized) {
    try {
        InventoryController dummyController(dpMock, nullptr);
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(), std::string("Received a nulltpr argument"));
    }
    catch(...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

TEST_F(TestInventory, InitWithDataNotInitialized) {
    try {
        InventoryController dummyController(nullptr, viewMock);
        FAIL() << "Expected std::invalid_argument";
    }
    catch(std::invalid_argument const & err) {
        EXPECT_EQ(err.what(), std::string("Received a nulltpr argument"));
    }
    catch(...) {
        FAIL() << "Expected std::invalid_argument";
    }
}

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
    // Should return a valid product data (valid barcode)
    ASSERT_FALSE(inventoryController.getProduct(requestedBarcode).barcode().empty());
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
    // Should return an empty product data (empty barcode)
    ASSERT_TRUE(inventoryController.getProduct(requestedBarcode).barcode().empty());
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
                 "L", "12", "High", "10.000", "text.00",
                 "DummySupplier", "DummySupplierCode");
    std::map<std::string, std::string> dummyValidationContainer;

    // Setup valid UOM
    EXPECT_CALL(*dpMock, getUOMs())
        .WillOnce(Return(
                std::vector<entity::UnitOfMeasurement>{
                    entity::UnitOfMeasurement("1", "Liter", "L")}));

    ASSERT_EQ(inventoryController.save(dummyProduct, &dummyValidationContainer),
              INVENTORYAPISTATUS::FAILED);
    // Validation result must contain two errors
    ASSERT_EQ(dummyValidationContainer.size(), 2);
}

TEST_F(TestInventory, TestSaveWithInvalidSellingPrice) {
    // Fake that selling price is lesser than the original price
    entity::Product dummyProduct("DUMMY-BARCODE-123", "DUMMY-SKU", "ProductName",
                 "Description", "DummyCategory", "SomeBrand",
                 "L", "12", "High", "10.00", "9.00",
                 "DummySupplier", "DummySupplierCode");
    std::map<std::string, std::string> dummyValidationContainer;

    // Setup valid UOM
    EXPECT_CALL(*dpMock, getUOMs())
        .WillOnce(Return(
                std::vector<entity::UnitOfMeasurement>{
                    entity::UnitOfMeasurement("1", "Liter", "L")}));

    ASSERT_EQ(inventoryController.save(dummyProduct, &dummyValidationContainer),
              INVENTORYAPISTATUS::FAILED);
    // Validation result must contain one error
    ASSERT_EQ(dummyValidationContainer.size(), 1);
}

TEST_F(TestInventory, TestSaveWithInvalidUOM) {
    // Fake that selling price is lesser than the original price
    entity::Product dummyProduct("DUMMY-BARCODE-123", "DUMMY-SKU", "ProductName",
                 "Description", "DummyCategory", "SomeBrand",
                 // Fake that the measurement is invalid
                 "InvalidMeasureMent", "12", "High", "9.00", "10.00",
                 "DummySupplier", "DummySupplierCode");
    std::map<std::string, std::string> dummyValidationContainer;

    // Fake that we have a valid UOM that will be compared with "InvalidMeasureMent"
    EXPECT_CALL(*dpMock, getUOMs())
        .WillOnce(Return(
                std::vector<entity::UnitOfMeasurement>{
                    entity::UnitOfMeasurement("1", "Liter", "L")}));

    ASSERT_EQ(inventoryController.save(dummyProduct, &dummyValidationContainer),
              INVENTORYAPISTATUS::FAILED);
    // Validation result must contain one error
    ASSERT_EQ(dummyValidationContainer.size(), 1);
}

TEST_F(TestInventory, TestSaveWithEmptyUOMRecord) {
    // Fake that selling price is lesser than the original price
    entity::Product dummyProduct("DUMMY-BARCODE-123", "DUMMY-SKU", "ProductName",
                 "Description", "DummyCategory", "SomeBrand",
                 // Fake that the measurement is invalid
                 "InvalidMeasureMent", "12", "High", "9.00", "10.00",
                 "DummySupplier", "DummySupplierCode");
    std::map<std::string, std::string> dummyValidationContainer;

    // Fake that we don't have any saved UOM
    EXPECT_CALL(*dpMock, getUOMs())
        .WillOnce(Return(
                std::vector<entity::UnitOfMeasurement>{}));

    // Should succeed
    ASSERT_EQ(inventoryController.save(dummyProduct, &dummyValidationContainer),
              INVENTORYAPISTATUS::SUCCESS);
    // Validation result must be empty
    ASSERT_TRUE(dummyValidationContainer.empty());
}


TEST_F(TestInventory, TestCreateProduct) {
    std::map<std::string, std::string> dummyValidationContainer;

    // Setup valid UOM
    EXPECT_CALL(*dpMock, getUOMs())
        .WillOnce(Return(
                std::vector<entity::UnitOfMeasurement>{
                    entity::UnitOfMeasurement("1", "Liter", "L")}));

    // Must perform the create call
    EXPECT_CALL(*dpMock, create(_));

    ASSERT_EQ(inventoryController.save(validProduct, &dummyValidationContainer),
              INVENTORYAPISTATUS::SUCCESS);
    // Validation result must be empty
    ASSERT_TRUE(dummyValidationContainer.empty());
}

TEST_F(TestInventory, TestUpdateProduct) {
    std::map<std::string, std::string> dummyValidationContainer;
    const std::string newStockValue("10");
    // Fake that there is at least one product data on record
    EXPECT_CALL(*dpMock, getProducts())
        .WillOnce(Return(std::vector<entity::Product>{validProduct}));
    // Cache the list
    inventoryController.list();

    // Setup valid UOM
    EXPECT_CALL(*dpMock, getUOMs())
        .WillOnce(Return(
                std::vector<entity::UnitOfMeasurement>{
                    entity::UnitOfMeasurement("1", "Liter", "L")}));

    // Fake that we updated the stock cound
    validProduct.setStock(newStockValue);

    // Must perform the update call
    EXPECT_CALL(*dpMock, update(_));

    ASSERT_EQ(inventoryController.save(validProduct, &dummyValidationContainer),
              INVENTORYAPISTATUS::SUCCESS);
    ASSERT_STREQ(inventoryController.getProduct(validProduct.barcode()).stock().c_str(),
                 newStockValue.c_str());
}

TEST_F(TestInventory, TestSaveUOM) {
    // Must perform the create call
    EXPECT_CALL(*dpMock, createUOM(_));

    ASSERT_EQ(inventoryController.save(entity::UnitOfMeasurement("2", "Kilogram", "kg")),
              INVENTORYAPISTATUS::SUCCESS);
}

TEST_F(TestInventory, TestSaveUOMWithExistingID) {
    // Setup an existing UOM
    EXPECT_CALL(*dpMock, getUOMs())
        .WillOnce(Return(
                std::vector<entity::UnitOfMeasurement>{
                    entity::UnitOfMeasurement("1", "Liter", "L")}));
    inventoryController.getMeasurementList();

    // Fake that we're saving the same ID (1)
    ASSERT_EQ(inventoryController.save(entity::UnitOfMeasurement("1", "Kilogram", "kg")),
              INVENTORYAPISTATUS::FAILED);
}

TEST_F(TestInventory, TestSaveUOMWithExistingName) {
    // Setup an existing UOM
    EXPECT_CALL(*dpMock, getUOMs())
        .WillOnce(Return(
                std::vector<entity::UnitOfMeasurement>{
                    entity::UnitOfMeasurement("1", "Liter", "L")}));
    inventoryController.getMeasurementList();

    // Fake that we're saving the same name (Liter)
    ASSERT_EQ(inventoryController.save(entity::UnitOfMeasurement("2", "Liter", "kg")),
              INVENTORYAPISTATUS::FAILED);
}

TEST_F(TestInventory, TestSaveUOMWithExistingAbbreviation) {
    // Setup an existing UOM
    EXPECT_CALL(*dpMock, getUOMs())
        .WillOnce(Return(
                std::vector<entity::UnitOfMeasurement>{
                    entity::UnitOfMeasurement("1", "Liter", "L")}));
    inventoryController.getMeasurementList();

    // Fake that we're saving the same name (L)
    ASSERT_EQ(inventoryController.save(entity::UnitOfMeasurement("2", "Kilogram", "L")),
              INVENTORYAPISTATUS::FAILED);
}

TEST_F(TestInventory, TestRemoveUOM) {
    // Setup an existing UOM
    EXPECT_CALL(*dpMock, getUOMs())
        .WillOnce(Return(
                std::vector<entity::UnitOfMeasurement>{
                    entity::UnitOfMeasurement("1", "Liter", "L")}));
    inventoryController.getMeasurementList();

    // Must perform the removeUOM call
    EXPECT_CALL(*dpMock, removeUOM(_));

    ASSERT_EQ(inventoryController.removeUOM("1"), INVENTORYAPISTATUS::SUCCESS);
}

TEST_F(TestInventory, TestRemoveUOMWithIDNotFound) {
    // Setup an existing UOM
    EXPECT_CALL(*dpMock, getUOMs())
        .WillOnce(Return(
                std::vector<entity::UnitOfMeasurement>{
                    entity::UnitOfMeasurement("1", "Liter", "L")}));
    inventoryController.getMeasurementList();

    // Fake that we're removing a non-exisitng ID (2)
    ASSERT_EQ(inventoryController.removeUOM("2"), INVENTORYAPISTATUS::NOT_FOUND);
}

}  // namespace test
}  // namespace inventory
}  // namespace domain
