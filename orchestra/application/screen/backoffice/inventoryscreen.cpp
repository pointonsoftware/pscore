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
#include "inventoryscreen.hpp"
#include <iostream>
#include <memory>
// view
#include <screencommon.hpp>
// core
#include <domain/inventory/interface/inventoryiface.hpp>
// data
#include <inventorydata.hpp>

namespace screen {
namespace inventory {

void InventoryScreen::show(std::promise<defines::display>* promise) {
    SCREENCOMMON().showTopBanner("Inventory Control");
    std::cout << "No data." << std::endl;
    std::string input;
    std::cin >> input;
    promise->set_value(defines::display::DASHBOARD);
}

}  // namespace inventory
}  // namespace screen
