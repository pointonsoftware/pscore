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
#ifndef CORE_ENTITY_VALIDATOR_CONTACTDETAILSVALIDATOR_HPP_
#define CORE_ENTITY_VALIDATOR_CONTACTDETAILSVALIDATOR_HPP_
#include <string>
// Parent
#include "validator.hpp"
// Entity
#include <contactdetails.hpp>

namespace entity {
namespace validator {

/*!
 * Phone number validation rules:
 * - phone numbers can be empty
 * - phone number must only contain numbers
 * - phone numbers should be 10 digits in length
*/
constexpr unsigned int MAX_PHONE_NUMBER_LENGTH = 10;

/*!
 * Email address validation rules:
 * - must contain an "@" character
*/

class ContactDetailsValidator : public Validator {
 public:
    explicit ContactDetailsValidator(const ContactDetails& contactDetails);
    ~ContactDetailsValidator() = default;

    // Validation functions
    void validatePhoneNumbers();
    void validateEmailAddress();

 private:
    ContactDetails mContactDetails;
    ValidationResult phoneNumberSanity(const std::string& number);
};

}  // namespace validator
}  // namespace entity
#endif  // CORE_ENTITY_VALIDATOR_CONTACTDETAILSVALIDATOR_HPP_