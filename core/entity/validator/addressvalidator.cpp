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
#include "addressvalidator.hpp"
#include <regex>
#include <string>

namespace entity {
namespace validator {

AddressValidator::AddressValidator(const Address& address) {
    mAddress = address;
    validationFunctions.emplace_back(std::bind(&AddressValidator::validateHouseNumber, this));
    validationFunctions.emplace_back(std::bind(&AddressValidator::validateLot, this));
    validationFunctions.emplace_back(std::bind(&AddressValidator::validateBlock, this));
    validationFunctions.emplace_back(std::bind(&AddressValidator::validateStreet, this));
    validationFunctions.emplace_back(std::bind(&AddressValidator::validateSubdivision, this));
    validationFunctions.emplace_back(std::bind(&AddressValidator::validatePurok, this));
    validationFunctions.emplace_back(std::bind(&AddressValidator::validateBarangay, this));
    validationFunctions.emplace_back(std::bind(&AddressValidator::validateCityTown, this));
    validationFunctions.emplace_back(std::bind(&AddressValidator::validateProvince, this));
    validationFunctions.emplace_back(std::bind(&AddressValidator::validateZipCode, this));

    validate();
}

ValidationResult AddressValidator::sanity(const std::string& str) {
    if (str.empty()) {
        return ValidationResult::S_OK;
    }
    if (std::regex_search(str, std::regex(INVALID_ADDRESS_CHARACTERS))) {
        return ValidationResult::S_INVALID_STRING;
    }
    return ValidationResult::S_OK;
}

void AddressValidator::validateHouseNumber() {
    mResult = sanity(mAddress.housenumber);
}
void AddressValidator::validateLot() {
    mResult = sanity(mAddress.lot);
}
void AddressValidator::validateBlock() {
    mResult = sanity(mAddress.block);
}
void AddressValidator::validateStreet() {
    mResult = sanity(mAddress.street);
}
void AddressValidator::validateSubdivision() {
    mResult = sanity(mAddress.subdivision);
}
void AddressValidator::validateSitio() {
    mResult = sanity(mAddress.sitio);
}
void AddressValidator::validatePurok() {
    mResult = sanity(mAddress.purok);
}
void AddressValidator::validateBarangay() {
    mResult = sanity(mAddress.barangay);
}
void AddressValidator::validateCityTown() {
    mResult = sanity(mAddress.city_town);
}
void AddressValidator::validateProvince() {
    mResult = sanity(mAddress.province);
}
void AddressValidator::validateZipCode() {
    mResult = sanity(mAddress.zip);
}
}  // namespace validator
}  // namespace entity
