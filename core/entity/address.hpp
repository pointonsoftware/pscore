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
#ifndef CORE_ENTITY_ADDRESS_HPP_
#define CORE_ENTITY_ADDRESS_HPP_

#include <string>

namespace entity {

// Fields
constexpr char FIELD_ADDR_HNO[] = "Entity.Field.HouseNumber";
constexpr char FIELD_ADDR_LOT[] = "Entity.Field.Lot";
constexpr char FIELD_ADDR_BLK[] = "Entity.Field.Block";
constexpr char FIELD_ADDR_STR[] = "Entity.Field.Street";
constexpr char FIELD_ADDR_SDV[] = "Entity.Field.Subdivision";
constexpr char FIELD_ADDR_SIT[] = "Entity.Field.Sitio";
constexpr char FIELD_ADDR_PRK[] = "Entity.Field.Purok";
constexpr char FIELD_ADDR_BRG[] = "Entity.Field.Barangay";
constexpr char FIELD_ADDR_CTY[] = "Entity.Field.CityTown";
constexpr char FIELD_ADDR_PRV[] = "Entity.Field.Province";
constexpr char FIELD_ADDR_ZIP[] = "Entity.Field.Zip";

struct Address {
    std::string housenumber;
    std::string lot;
    std::string block;
    std::string street;
    std::string subdivision;
    std::string sitio;
    std::string purok;
    std::string barangay;
    std::string city_town;
    std::string province;
    std::string zip;
};

}  // namespace entity
#endif  // CORE_ENTITY_ADDRESS_HPP_