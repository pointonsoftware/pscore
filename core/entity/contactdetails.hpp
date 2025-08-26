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
#ifndef CORE_ENTITY_CONTACTDETAILS_HPP_
#define CORE_ENTITY_CONTACTDETAILS_HPP_

#include <string>
#include <vector>

namespace entity {

// Fields
constexpr char FIELD_CONT_PH1[] = "ContactDetails.Phone1";
constexpr char FIELD_CONT_PH2[] = "ContactDetails.Phone2";
constexpr char FIELD_CONT_EML[] = "ContactDetails.Email";

class ContactDetails {
 public:
    ContactDetails(const std::string& email, const std::string& phone1, const std::string& phone2)
                   : mEmail(email), mPhone1(phone1), mPhone2(phone2) {}
    ContactDetails() = default;
    ~ContactDetails() = default;
     // Setters
    void setEmail(const std::string& str) {
        mEmail = str;
    }
    void setPhone1(const std::string& str) {
        mPhone1 = str;
    }
    void setPhone2(const std::string& str) {
        mPhone2 = str;
    }
    // Getters
    const std::string& email() const {
        return mEmail;
    }
    const std::string& phone1() const {
        return mPhone1;
    }
    const std::string& phone2() const {
        return mPhone2;
    }

 private:
    std::string mEmail;
    std::string mPhone1;
    std::string mPhone2;
};

}  // namespace entity
#endif  // CORE_ENTITY_CONTACTDETAILS_HPP_