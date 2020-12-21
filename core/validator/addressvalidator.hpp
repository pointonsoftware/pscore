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
#ifndef CORE_VALIDATOR_ADDRESSVALIDATOR_HPP_
#define CORE_VALIDATOR_ADDRESSVALIDATOR_HPP_
#include <string>
// Parent
#include "validator.hpp"
// Entity
#include <entity/address.hpp>

namespace entity {
namespace validator {

/*!
 * Validation Rules:
 * - Address fields can be empty except for City/Town and Province
 * - City/Town and Province can only contain alphabet, numbers, space, dots and dashes
 * - Address Line 1 and Line 2 can contain alphabet, numbers, space, dots, dashes, and commas
*/
constexpr char INVALID_CTPZ_CHARACTERS[] = "[^a-zA-Z0-9\\-. ]";  // for city, town, province and Zip
constexpr char INVALID_ADDRLINE_CHARACTERS[] = "[^a-zA-Z0-9\\-., ]";  // for address lines 1 and 2

class AddressValidator : public Validator {
 public:
    explicit AddressValidator(const Address& address);
    ~AddressValidator() = default;

 private:
    const Address mAddress;
    // Validation functions
    ValidationStatus validateLine1();
    ValidationStatus validateLine2();
    ValidationStatus validateCityTown();
    ValidationStatus validateProvince();
    ValidationStatus validateZipCode();

    ValidationStatus sanity(const std::string& str, const std::string& invalidChars) const;
};

}  // namespace validator
}  // namespace entity
#endif  // CORE_VALIDATOR_ADDRESSVALIDATOR_HPP_