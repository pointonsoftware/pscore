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
#ifndef CORE_ENTITY_VALIDATOR_ADDRESSVALIDATOR_HPP_
#define CORE_ENTITY_VALIDATOR_ADDRESSVALIDATOR_HPP_
#include <string>
// Parent
#include "validator.hpp"
// Entity
#include <entity/address.hpp>

namespace entity {
namespace validator {

/*!
 * Validation Rules:
 * - Address can be empty
 * - Address can only contain alphabet, numbers, dots and dashes
*/
constexpr char INVALID_ADDRESS_CHARACTERS[] = "[^a-zA-Z0-9\\-. ]";

// Fields
constexpr char FIELD_ADDR_HNO[] = "housenumber";
constexpr char FIELD_ADDR_LOT[] = "lot";
constexpr char FIELD_ADDR_BLK[] = "block";
constexpr char FIELD_ADDR_STR[] = "street";
constexpr char FIELD_ADDR_SDV[] = "subdivision";
constexpr char FIELD_ADDR_SIT[] = "sitio";
constexpr char FIELD_ADDR_PRK[] = "purok";
constexpr char FIELD_ADDR_BRG[] = "barangay";
constexpr char FIELD_ADDR_CTY[] = "city_town";
constexpr char FIELD_ADDR_PRV[] = "province";
constexpr char FIELD_ADDR_ZIP[] = "zip";

class AddressValidator : public Validator {
 public:
    explicit AddressValidator(const Address& address);
    ~AddressValidator() = default;

 private:
    Address mAddress;
    // Validation functions
    ValidationStatus validateHouseNumber();
    ValidationStatus validateLot();
    ValidationStatus validateBlock();
    ValidationStatus validateStreet();
    ValidationStatus validateSubdivision();
    ValidationStatus validateSitio();
    ValidationStatus validatePurok();
    ValidationStatus validateBarangay();
    ValidationStatus validateCityTown();
    ValidationStatus validateProvince();
    ValidationStatus validateZipCode();

    ValidationStatus sanity(const std::string& str) const;
};

}  // namespace validator
}  // namespace entity
#endif  // CORE_ENTITY_VALIDATOR_ADDRESSVALIDATOR_HPP_