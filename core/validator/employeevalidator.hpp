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
#ifndef CORE_VALIDATOR_EMPLOYEEVALIDATOR_HPP_
#define CORE_VALIDATOR_EMPLOYEEVALIDATOR_HPP_
// Parent
#include "validator.hpp"
// Entity
#include <entity/employee.hpp>

namespace entity {
namespace validator {

/*!
 * Validation Rules:
 * - Employee ID cannot be empty
*/
class EmployeeValidator : public Validator {
 public:
    explicit EmployeeValidator(const Employee& employee);
    ~EmployeeValidator() = default;

 private:
    const Employee mEmployee;
    // Validation functions
    ValidationStatus validateID();
    ValidationStatus validatePosition();
    ValidationStatus validateStatus();
};

}  // namespace validator
}  // namespace entity
#endif  // CORE_VALIDATOR_EMPLOYEEVALIDATOR_HPP_