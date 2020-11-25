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
#include "personvalidator.hpp"

namespace entity {
namespace validator {

PersonValidator::PersonValidator(const Person& person) {
    mPerson = person;
    validationFunctions.emplace_back(std::bind(&PersonValidator::validateFirstName, this));
    validationFunctions.emplace_back(std::bind(&PersonValidator::validateMiddleName, this));
    validationFunctions.emplace_back(std::bind(&PersonValidator::validateLastName, this));
    validationFunctions.emplace_back(std::bind(&PersonValidator::validateGender, this));
    validationFunctions.emplace_back(std::bind(&PersonValidator::validateBirthdate, this));
    validate();
}

ValidationStatus PersonValidator::validateFirstName() {
    if (mPerson.firstName().empty()) {
        addError(FIELD_FNAME, "First Name cannot be empty.");
        return ValidationStatus::S_EMPTY;
    }
    return ValidationStatus::S_OK;
}
ValidationStatus PersonValidator::validateMiddleName() {
    return ValidationStatus::S_OK;
}
ValidationStatus PersonValidator::validateLastName() {
    if (mPerson.lastName().empty()) {
        addError(FIELD_LNAME, "Last Name cannot be empty.");
        return ValidationStatus::S_EMPTY;
    }
    return ValidationStatus::S_OK;
}
ValidationStatus PersonValidator::validateGender() {
    if (mPerson.gender().empty()) {
        addError(FIELD_GENDER, "Gender cannot be empty.");
        return ValidationStatus::S_EMPTY;
    }
    return ValidationStatus::S_OK;
}
ValidationStatus PersonValidator::validateBirthdate() {
    // Todo (code) - validate birthdate
    return ValidationStatus::S_OK;
}
}  // namespace validator
}  // namespace entity
