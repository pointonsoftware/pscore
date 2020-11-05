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
#ifndef CORE_ENTITY_VALIDATOR_ADDRESSVALIDATOR_HPP_
#define CORE_ENTITY_VALIDATOR_ADDRESSVALIDATOR_HPP_
#include <string>
// Parent
#include "validator.hpp"
// Entity
#include <address.hpp>

namespace entity {
namespace validator {

/*!
 * Validation Rules:
 * - Address can be empty
 * - Address can only contain alphabet, numbers, dots and dashes
*/

constexpr char INVALID_ADDRESS_CHARACTERS[] = "[^a-zA-Z0-9\\-. ]";

class AddressValidator : public Validator {
 public:
    explicit AddressValidator(const Address& address);
    ~AddressValidator() = default;

 private:
    Address mAddress;
    // Validation functions
    void validateHouseNumber();
    void validateLot();
    void validateBlock();
    void validateStreet();
    void validateSubdivision();
    void validateSitio();
    void validatePurok();
    void validateBarangay();
    void validateCityTown();
    void validateProvince();
    void validateZipCode();

    ValidationResult sanity(const std::string& str);
};

}  // namespace validator
}  // namespace entity
#endif  // CORE_ENTITY_VALIDATOR_ADDRESSVALIDATOR_HPP_