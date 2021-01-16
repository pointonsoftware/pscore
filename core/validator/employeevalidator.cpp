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
#include "employeevalidator.hpp"
#include <regex>
#include <general.hpp>  // pscore utility

namespace entity {
namespace validator {

EmployeeValidator::EmployeeValidator(const Employee& employee) : mEmployee(employee) {
    validationFunctions.emplace_back(std::bind(&EmployeeValidator::validateID, this));
    validationFunctions.emplace_back(std::bind(&EmployeeValidator::validatePosition, this));
    validationFunctions.emplace_back(std::bind(&EmployeeValidator::validateStatus, this));
    validate();
}

ValidationStatus EmployeeValidator::validateID() {
    if (mEmployee.ID().empty()) {
        addError(FIELD_EMPID, "Employee ID must not be empty.");
        return ValidationStatus::S_EMPTY;
    }
    return ValidationStatus::S_OK;
}

ValidationStatus EmployeeValidator::validatePosition() {
    if (mEmployee.position().empty()) {
        addError(FIELD_EPOS, "Employee position must not be empty.");
        return ValidationStatus::S_EMPTY;
    }
    return ValidationStatus::S_OK;
}

ValidationStatus EmployeeValidator::validateStatus() {
    if (mEmployee.status().empty()) {
        addError(FIELD_ESTATUS, "Employee status must not be empty.");
        return ValidationStatus::S_EMPTY;
    }
    if (utility::toUpper(mEmployee.status()) != "ACTIVE"
        && utility::toUpper(mEmployee.status()) != "ON-LEAVE"
        && utility::toUpper(mEmployee.status()) != "INACTIVE") {
        addError(FIELD_ESTATUS, "Employee status must be ACTIVE, ON-LEAVE or INACTIVE.");
        return ValidationStatus::S_INVALID_STRING;
    }
    return ValidationStatus::S_OK;
}

}  // namespace validator
}  // namespace entity
