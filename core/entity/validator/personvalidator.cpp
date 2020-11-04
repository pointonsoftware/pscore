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

void PersonValidator::validateFirstName() {
    mResult = ValidationResult::S_OK;
}
void PersonValidator::validateMiddleName() {
    mResult = ValidationResult::S_OK;
}
void PersonValidator::validateLastName() {
    mResult = ValidationResult::S_OK;
}
}  // namespace validator
}  // namespace entity
