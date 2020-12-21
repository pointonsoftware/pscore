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
#ifndef CORE_DOMAIN_UNITTEST_MOCK_INVENTORY_INVENTORYVIEWMOCK_HPP_
#define CORE_DOMAIN_UNITTEST_MOCK_INVENTORY_INVENTORYVIEWMOCK_HPP_
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <domain/inventory/interface/inventoryviewif.hpp>

namespace domain {
namespace inventory {

class InventoryViewMock : public InventoryViewInterface {
 public:
    InventoryViewMock() = default;
    ~InventoryViewMock() = default;
};

}  // namespace inventory
}  // namespace domain

#endif  // CORE_DOMAIN_UNITTEST_MOCK_INVENTORY_INVENTORYVIEWMOCK_HPP_