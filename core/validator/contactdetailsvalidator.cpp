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
#include <general.hpp>  // pscore utility

namespace entity {
namespace validator {

ContactDetailsValidator::ContactDetailsValidator(const ContactDetails& contactDetails)
                                                 : mContactDetails(contactDetails) {
    validationFunctions.emplace_back(
                        std::bind(&ContactDetailsValidator::validatePhoneNumber1, this));
    validationFunctions.emplace_back(
                        std::bind(&ContactDetailsValidator::validatePhoneNumber2, this));
    validationFunctions.emplace_back(
                        std::bind(&ContactDetailsValidator::validateEmailAddress, this));
    validate();
}

ValidationStatus ContactDetailsValidator::phoneNumberSanity(const std::string& number) const {
    if (number.empty()) {
        return ValidationStatus::S_OK;
    }
    if (!utility::isNumber(number)) {
        return ValidationStatus::S_INVALID_STRING;
    }
    if (number.size() != PHONE_NUMBER_LENGTH) {
        return ValidationStatus::S_INVALID_SIZE;
    }
    return ValidationStatus::S_OK;
}

ValidationStatus ContactDetailsValidator::validatePhoneNumber1() {
    ValidationStatus retVal = phoneNumberSanity(mContactDetails.phone1());
    switch (retVal) {
        case ValidationStatus::S_INVALID_STRING:
            addError(FIELD_CONT_PH1, "Phone number 1 contains invalid character.");
            break;
        case ValidationStatus::S_INVALID_SIZE:
            addError(FIELD_CONT_PH1, "Phone number 1 is invalid.");
            break;
        default:
            break;
    }
    return retVal;
}

ValidationStatus ContactDetailsValidator::validatePhoneNumber2() {
    ValidationStatus retVal = phoneNumberSanity(mContactDetails.phone2());
    switch (retVal) {
        case ValidationStatus::S_INVALID_STRING:
            addError(FIELD_CONT_PH2, "Phone number 2 contains invalid character.");
            break;
        case ValidationStatus::S_INVALID_SIZE:
            addError(FIELD_CONT_PH2, "Phone number 2 is invalid.");
            break;
        default:
            break;
    }
    return retVal;
}

ValidationStatus ContactDetailsValidator::validateEmailAddress() {
    if (mContactDetails.email().empty()) {
        return ValidationStatus::S_OK;
    }
    const std::string& email = mContactDetails.email();
    if (std::count(email.begin(), email.end(), '@') != 1) {
        addError(FIELD_CONT_EML, "Email address is invalid.");
        return ValidationStatus::S_INVALID_STRING;
    }
    return ValidationStatus::S_OK;
}

}  // namespace validator
}  // namespace entity
