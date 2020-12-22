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
    TestInventory() : inventoryController(dpMock, viewMock) {
        // Empty for now
    }

    ~TestInventory() = default;
    void SetUp() {}
    void TearDown() {}

    std::shared_ptr<InventoryDataMock> dpMock  = std::make_shared<InventoryDataMock>();
    std::shared_ptr<InventoryViewMock> viewMock = std::make_shared<InventoryViewMock>();
    InventoryController inventoryController;
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
                entity::Product("DUMMY-SKU", "", "", requestedBarcode, "", "", "", "", "",
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
                entity::Product("DUMMY-SKU", "", "", storedProduct, "", "", "", "", "",
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
                entity::Product("DUMMY-SKU", "", "", requestedBarcode, "", "", "", "", "",
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
                entity::Product("DUMMY-SKU", "", "", storedProduct, "", "", "", "", "",
                                "", "", "", "")}));
    // Cache the list
    inventoryController.list();
    EXPECT_CALL(*viewMock, showDataNotReadyScreen());
    ASSERT_EQ(inventoryController.remove(requestedBarcode), INVENTORYAPISTATUS::NOT_FOUND);
}

}  // namespace test
}  // namespace inventory
}  // namespace domain
