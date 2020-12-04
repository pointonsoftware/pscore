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
#include "uservalidator.hpp"
#include <general.hpp>  // pscore utility

namespace entity {
namespace validator {

UserValidator::UserValidator(const User& user) : mUser(user) {
    validationFunctions.emplace_back(std::bind(&UserValidator::validateUserID, this));
    validationFunctions.emplace_back(std::bind(&UserValidator::validateRole, this));
    validationFunctions.emplace_back(std::bind(&UserValidator::validatePIN, this));
    validate();
}
ValidationStatus UserValidator::validateUserID() {
    if (mUser.userID().empty()) {
        addError(FIELD_UID, " UserID must not be empty.");
        return ValidationStatus::S_INVALID_STRING;
    }
    return ValidationStatus::S_OK;
}
ValidationStatus UserValidator::validateRole() {
    if (mUser.role().empty()) {
        addError(FIELD_ROLE, " Role must not be empty.");
        return ValidationStatus::S_INVALID_STRING;
    }
    return ValidationStatus::S_OK;
}

ValidationStatus UserValidator::validatePIN() {
    if (!utility::isNumber(mUser.pin())) {
        addError(FIELD_PIN, " PIN contains invalid character.");
        return ValidationStatus::S_INVALID_STRING;
    }
    if (mUser.pin().size() != PIN_SIZE) {
        addError(FIELD_PIN, "PIN character length is invalid.");
        return ValidationStatus::S_INVALID_SIZE;
    }
    return ValidationStatus::S_OK;
}

}  // namespace validator
}  // namespace entity
