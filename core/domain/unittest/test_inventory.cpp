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

TEST_F(TestInventory, SampleTest) {
    SUCCEED() << "SampleTest";
}

}  // namespace test
}  // namespace inventory
}  // namespace domain
