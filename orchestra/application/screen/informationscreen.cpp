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
#include "informationscreen.hpp"

namespace screen {

template <>
void InformationScreen<entity::Employee>::showBasicInformation() {  // specialize for employee
    SCREENCOMMON().printColumns({"Basic Information"}, true);
    printItem("First Name", mInfo->firstName());
    printItem("Middle Name", mInfo->middleName());
    printItem("Last Name", mInfo->lastName());
    printItem("Birthdate", mInfo->birthdate());
    printItem("Gender", mInfo->gender());
    printItem("Position", mInfo->position());
}

template <>
void InformationScreen<entity::Product>::showBasicInformation() {  // specialize for product
    SCREENCOMMON().printColumns({"Details"}, true);
    printItem("Barcode", mInfo->barcode());
    printItem("SKU", mInfo->sku());
    printItem("Name", mInfo->name());
    printItem("Description", mInfo->description());
    printItem("Category", mInfo->category());
    printItem("Brand", mInfo->brand());
    printItem("UOM", mInfo->uom());
    printItem("Stocks", mInfo->stock());
    printItem("Status", mInfo->status());
    printItem("Orig. Price", mInfo->originalPrice());
    printItem("Sell Price", mInfo->sellPrice());
    printItem("Supplier", mInfo->supplierName());
    printItem("Suppl. Code", mInfo->supplierCode());
}

}  // namespace screen