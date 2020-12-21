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
#include "uservalidator.hpp"
#include <iomanip>
#include <sstream>
#include <general.hpp>  // pscore utility

namespace entity {
namespace validator {

UserValidator::UserValidator(const User& user) : mUser(user) {
    validationFunctions.emplace_back(std::bind(&UserValidator::validateUserID, this));
    validationFunctions.emplace_back(std::bind(&UserValidator::validateRole, this));
    validationFunctions.emplace_back(std::bind(&UserValidator::validatePIN, this));
    validationFunctions.emplace_back(std::bind(&UserValidator::validateCreatedAt, this));
    validate();
}

ValidationStatus UserValidator::validateUserID() {
    if (mUser.userID().empty()) {
        addError(FIELD_UID, "UserID must not be empty.");
        return ValidationStatus::S_INVALID_STRING;
    }
    return ValidationStatus::S_OK;
}
ValidationStatus UserValidator::validateRole() {
    if (mUser.role().empty()) {
        addError(FIELD_ROLE, "Role must not be empty.");
        return ValidationStatus::S_INVALID_STRING;
    }
    return ValidationStatus::S_OK;
}

ValidationStatus UserValidator::validatePIN() {
    if (!utility::isNumber(mUser.pin())) {
        addError(FIELD_PIN, "PIN contains invalid character.");
        return ValidationStatus::S_INVALID_STRING;
    }
    if (mUser.pin().size() != PIN_SIZE) {
        addError(FIELD_PIN, "PIN character length is invalid.");
        return ValidationStatus::S_INVALID_SIZE;
    }
    return ValidationStatus::S_OK;
}

ValidationStatus UserValidator::validateCreatedAt() {
    /**
    * Code based-from StackOverflow by alain
    * Author profile: https://stackoverflow.com/users/3435400/alain
    *
    * Original question: https://stackoverflow.com/q/39447921/3975468
    * Answer: https://stackoverflow.com/a/39452595/3975468
    */
    std::istringstream date_s(mUser.createdAt());
    struct tm date_c, date_c_cmp;
    date_s >> std::get_time(&date_c, "%d-%m-%Y %H:%M:%S");
    date_c_cmp = date_c;  // store original  to compare later
    std::mktime(& date_c);  // normalize

    // Compare with original
    if (date_c.tm_year != date_c_cmp.tm_year
        || date_c.tm_mon != date_c_cmp.tm_mon
        || date_c.tm_mday != date_c_cmp.tm_mday
        || date_c.tm_hour != date_c_cmp.tm_hour
        || date_c.tm_min != date_c_cmp.tm_min
        || date_c.tm_sec != date_c_cmp.tm_sec) {
        addError(FIELD_CDATE, "CreatedAt is an invalid date-time string.");
        return ValidationStatus::S_INVALID_STRING;
    }
    return ValidationStatus::S_OK;
}

}  // namespace validator
}  // namespace entity
