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
    validate();
}

ValidationStatus PersonValidator::validateFirstName() const {
    return ValidationStatus::S_OK;
}
ValidationStatus PersonValidator::validateMiddleName() const {
    return ValidationStatus::S_OK;
}
ValidationStatus PersonValidator::validateLastName() const {
    return ValidationStatus::S_OK;
}

// Todo (code) - validate birthdate

}  // namespace validator
}  // namespace entity
