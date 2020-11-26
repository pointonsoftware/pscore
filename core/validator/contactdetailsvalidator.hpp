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
#ifndef CORE_VALIDATOR_CONTACTDETAILSVALIDATOR_HPP_
#define CORE_VALIDATOR_CONTACTDETAILSVALIDATOR_HPP_
#include <string>
// Parent
#include "validator.hpp"
// Entity
#include <entity/contactdetails.hpp>

namespace entity {
namespace validator {

/*!
 * Email address validation rules:
 * - email address can be empty
 * - must contain an "@" character
*/

/*!
 * Phone number validation rules:
 * - phone numbers can be empty
 * - phone number must only contain numbers
 * - phone numbers should be 11 digits in length
*/
constexpr unsigned int PHONE_NUMBER_LENGTH = 11;

// Fields
constexpr char FIELD_CONT_PH1[] = "Entity.Field.Phone1";
constexpr char FIELD_CONT_PH2[] = "Entity.Field.Phone2";
constexpr char FIELD_CONT_EML[] = "Entity.Field.Email";

class ContactDetailsValidator : public Validator {
 public:
    explicit ContactDetailsValidator(const ContactDetails& contactDetails);
    ~ContactDetailsValidator() = default;

 private:
    const ContactDetails mContactDetails;
    ValidationStatus validatePhoneNumber1();
    ValidationStatus validatePhoneNumber2();
    ValidationStatus validateEmailAddress();
    ValidationStatus phoneNumberSanity(const std::string& number) const;
};

}  // namespace validator
}  // namespace entity
#endif  // CORE_VALIDATOR_CONTACTDETAILSVALIDATOR_HPP_