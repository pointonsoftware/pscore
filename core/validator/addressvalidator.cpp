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

AddressValidator::AddressValidator(const Address& address) : mAddress(address) {
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

ValidationStatus AddressValidator::sanity(const std::string& str) const {
    if (str.empty()) {
        return ValidationStatus::S_OK;
    }
    if (std::regex_search(str, std::regex(INVALID_ADDRESS_CHARACTERS))) {
        return ValidationStatus::S_INVALID_STRING;
    }
    return ValidationStatus::S_OK;
}

ValidationStatus AddressValidator::validateHouseNumber() {
    ValidationStatus retVal = sanity(mAddress.housenumber);
    if (retVal == ValidationStatus::S_INVALID_STRING) {
        addError(FIELD_ADDR_HNO, "House number contains invalid character.");
    }
    return retVal;
}
ValidationStatus AddressValidator::validateLot() {
    ValidationStatus retVal = sanity(mAddress.lot);
    if (retVal == ValidationStatus::S_INVALID_STRING) {
        addError(FIELD_ADDR_LOT, "Lot contains invalid character.");
    }
    return retVal;
}
ValidationStatus AddressValidator::validateBlock() {
    ValidationStatus retVal = sanity(mAddress.block);
    if (retVal == ValidationStatus::S_INVALID_STRING) {
        addError(FIELD_ADDR_BLK, "Block contains invalid character.");
    }
    return retVal;
}
ValidationStatus AddressValidator::validateStreet() {
    ValidationStatus retVal = sanity(mAddress.street);
    if (retVal == ValidationStatus::S_INVALID_STRING) {
        addError(FIELD_ADDR_STR, "Street contains invalid character.");
    }
    return retVal;
}
ValidationStatus AddressValidator::validateSubdivision() {
    ValidationStatus retVal = sanity(mAddress.subdivision);
    if (retVal == ValidationStatus::S_INVALID_STRING) {
        addError(FIELD_ADDR_SDV, "Subdivision contains invalid character.");
    }
    return retVal;
}
ValidationStatus AddressValidator::validateSitio() {
    ValidationStatus retVal = sanity(mAddress.sitio);
    if (retVal == ValidationStatus::S_INVALID_STRING) {
        addError(FIELD_ADDR_SIT, "Sitio contains invalid character.");
    }
    return retVal;
}
ValidationStatus AddressValidator::validatePurok() {
    ValidationStatus retVal = sanity(mAddress.purok);
    if (retVal == ValidationStatus::S_INVALID_STRING) {
        addError(FIELD_ADDR_PRK, "Purok contains invalid character.");
    }
    return retVal;
}
ValidationStatus AddressValidator::validateBarangay() {
    ValidationStatus retVal = sanity(mAddress.barangay);
    if (retVal == ValidationStatus::S_INVALID_STRING) {
        addError(FIELD_ADDR_BRG, "Barangay contains invalid character.");
    }
    return retVal;
}
ValidationStatus AddressValidator::validateCityTown() {
    if (mAddress.city_town.empty()) {
        addError(FIELD_ADDR_CTY, "City/Town cannot be empty.");
        return ValidationStatus::S_EMPTY;
    }
    ValidationStatus retVal = sanity(mAddress.city_town);
    if (retVal == ValidationStatus::S_INVALID_STRING) {
        addError(FIELD_ADDR_CTY, "City/Town contains invalid character.");
    }
    return retVal;
}
ValidationStatus AddressValidator::validateProvince() {
    if (mAddress.province.empty()) {
        addError(FIELD_ADDR_PRV, "Province cannot be empty.");
        return ValidationStatus::S_EMPTY;
    }
    ValidationStatus retVal = sanity(mAddress.province);
    if (retVal == ValidationStatus::S_INVALID_STRING) {
        addError(FIELD_ADDR_PRV, "Province contains invalid character.");
    }
    return retVal;
}
ValidationStatus AddressValidator::validateZipCode() {
    ValidationStatus retVal = sanity(mAddress.zip);
    if (retVal == ValidationStatus::S_INVALID_STRING) {
        addError(FIELD_ADDR_ZIP, "Zip contains invalid character.");
    }
    return retVal;
}
}  // namespace validator
}  // namespace entity
