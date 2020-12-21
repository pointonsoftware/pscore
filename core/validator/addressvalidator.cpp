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
    validationFunctions.emplace_back(std::bind(&AddressValidator::validateLine1, this));
    validationFunctions.emplace_back(std::bind(&AddressValidator::validateLine2, this));
    validationFunctions.emplace_back(std::bind(&AddressValidator::validateCityTown, this));
    validationFunctions.emplace_back(std::bind(&AddressValidator::validateProvince, this));
    validationFunctions.emplace_back(std::bind(&AddressValidator::validateZipCode, this));
    validate();
}

ValidationStatus AddressValidator::sanity(const std::string& str,
                                          const std::string& invalidChars) const {
    if (str.empty()) {
        return ValidationStatus::S_OK;
    }
    if (std::regex_search(str, std::regex(invalidChars))) {
        return ValidationStatus::S_INVALID_STRING;
    }
    return ValidationStatus::S_OK;
}

ValidationStatus AddressValidator::validateLine1() {
    ValidationStatus retVal = sanity(mAddress.line1, INVALID_ADDRLINE_CHARACTERS);
    if (retVal == ValidationStatus::S_INVALID_STRING) {
        addError(FIELD_ADDR_LN1, "Address Line 1 contains invalid character.");
    }
    return retVal;
}
ValidationStatus AddressValidator::validateLine2() {
    ValidationStatus retVal = sanity(mAddress.line2, INVALID_ADDRLINE_CHARACTERS);
    if (retVal == ValidationStatus::S_INVALID_STRING) {
        addError(FIELD_ADDR_LN2, "Address Line 2 contains invalid character.");
    }
    return retVal;
}
ValidationStatus AddressValidator::validateCityTown() {
    if (mAddress.city_town.empty()) {
        addError(FIELD_ADDR_CTY, "City/Town cannot be empty.");
        return ValidationStatus::S_EMPTY;
    }
    ValidationStatus retVal = sanity(mAddress.city_town, INVALID_CTPZ_CHARACTERS);
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
    ValidationStatus retVal = sanity(mAddress.province, INVALID_CTPZ_CHARACTERS);
    if (retVal == ValidationStatus::S_INVALID_STRING) {
        addError(FIELD_ADDR_PRV, "Province contains invalid character.");
    }
    return retVal;
}
ValidationStatus AddressValidator::validateZipCode() {
    ValidationStatus retVal = sanity(mAddress.zip, INVALID_CTPZ_CHARACTERS);
    if (retVal == ValidationStatus::S_INVALID_STRING) {
        addError(FIELD_ADDR_ZIP, "Zip contains invalid character.");
    }
    return retVal;
}
}  // namespace validator
}  // namespace entity
