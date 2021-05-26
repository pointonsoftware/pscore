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
#ifndef CORE_DOMAIN_UNITTEST_MOCK_INVENTORY_INVENTORYDATAMOCK_HPP_
#define CORE_DOMAIN_UNITTEST_MOCK_INVENTORY_INVENTORYDATAMOCK_HPP_
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <domain/inventory/interface/inventorydataif.hpp>

namespace domain {
namespace inventory {

class InventoryDataMock : public InventoryDataInterface {
 public:
    InventoryDataMock() = default;
    ~InventoryDataMock() = default;

    MOCK_METHOD(std::vector<entity::Product>, getProducts, ());
    MOCK_METHOD(void, removeWithBarcode, (const std::string& barcode));
    MOCK_METHOD(void, create, (const entity::Product& product));
    MOCK_METHOD(void, update, (const entity::Product& product));
    MOCK_METHOD(std::vector<entity::UnitOfMeasurement>, getUOMs, ());
    MOCK_METHOD(void, createUOM, (const entity::UnitOfMeasurement& uom));
    MOCK_METHOD(void, removeUOM, (const std::string& id));
    MOCK_METHOD(std::vector<std::string>, getCategories, ());
    MOCK_METHOD(void, createCategory, (const std::string& category));
    MOCK_METHOD(void, removeCategory, (const std::string& category));
};

}  // namespace inventory
}  // namespace domain

#endif  // CORE_DOMAIN_UNITTEST_MOCK_INVENTORY_INVENTORYDATAMOCK_HPP_