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
#include "contactdetailsvalidator.hpp"

namespace entity {
namespace validator {

ContactDetailsValidator::ContactDetailsValidator(const ContactDetails& contactDetails) {
    mContactDetails = contactDetails;
}

ValidationResult ContactDetailsValidator::phoneNumberSanity(const std::string& number) {
    if (number.empty()) {
        return ValidationResult::S_OK;
    }
    if (std::find_if(number.begin(), number.end(),
        [](unsigned char c) { return !std::isdigit(c); }) != number.end()) {
        return ValidationResult::S_INVALID_STRING;
    }
    if (number.size() != MAX_PHONE_NUMBER_LENGTH) {
        return ValidationResult::S_TOO_LONG;
    }
    return ValidationResult::S_OK;
}

void ContactDetailsValidator::validatePhoneNumbers() {
    mResult = phoneNumberSanity(mContactDetails.phone_number_1);
    // Continue only if first phone number is valid
    if (mResult != ValidationResult::S_OK) {
        /*!
        * Todo (spec)
        * - why fail if phone # 1 is invalid? 
        * - this rule might be too tight and needs updating
        */
        return;
    }
    mResult = phoneNumberSanity(mContactDetails.phone_number_2);
}

void ContactDetailsValidator::validateEmailAddress() {
    mResult = std::count(mContactDetails.email.begin(), mContactDetails.email.end(), '@') != 1 ?
              ValidationResult::S_INVALID_STRING : ValidationResult::S_OK;
}

}  // namespace validator
}  // namespace entity
