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
#include "personalidvalidator.hpp"
#include <regex>
#include <general.hpp>  // pscore utility

namespace entity {
namespace validator {

PersonalIDValidator::PersonalIDValidator(const PersonalId& personalID) : mPersonalID(personalID) {
    validationFunctions.emplace_back(std::bind(&PersonalIDValidator::validateIDType, this));
    validationFunctions.emplace_back(std::bind(&PersonalIDValidator::validateIDNumber, this));
    validate();
}

ValidationStatus PersonalIDValidator::validateIDType() {
    if (mPersonalID.type().empty()) {
        addError(FIELD_PNID_IDT, "ID Type must not be empty.");
        return ValidationStatus::S_EMPTY;
    }
    if (utility::hasNumber(mPersonalID.type())) {
        // Type must be alphabet
        addError(FIELD_PNID_IDT, "ID Type contains invalid character.");
        return ValidationStatus::S_INVALID_STRING;
    }
    return ValidationStatus::S_OK;
}

ValidationStatus PersonalIDValidator::validateIDNumber() {
    if (mPersonalID.number().empty()) {
        addError(FIELD_PNID_IDN, "ID Number must not be empty.");
        return ValidationStatus::S_EMPTY;
    }
    if (std::regex_search(mPersonalID.number(), std::regex(INVALID_ID_CHARACTERS))) {
        // ID number contains invalid characters
        addError(FIELD_PNID_IDN, "ID Number contains invalid character");
        return ValidationStatus::S_INVALID_STRING;
    }
    return ValidationStatus::S_OK;
}

}  // namespace validator
}  // namespace entity
