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
#ifndef CORE_ENTITY_ADDRESS_HPP_
#define CORE_ENTITY_ADDRESS_HPP_

#include <string>

namespace entity {

// Fields
constexpr char FIELD_ADDR_LN1[] = "Address.Line1";
constexpr char FIELD_ADDR_LN2[] = "Address.Line2";
constexpr char FIELD_ADDR_CTY[] = "Address.CityTown";
constexpr char FIELD_ADDR_PRV[] = "Address.Province";
constexpr char FIELD_ADDR_ZIP[] = "Address.Zip";

class Address {
 public:
    Address(const std::string& line1, const std::string& line2, const std::string& cityTown,
            const std::string& province, const std::string& zip) : mLine1(line1), mLine2(line2),
            mCityTown(cityTown), mProvince(province), mZIP(zip) {}
    Address() = default;
    ~Address() = default;
     // Setters
    void setLine1(const std::string& str) {
        mLine1 = str;
    }
    void setLine2(const std::string& str) {
        mLine2 = str;
    }
    void setCityTown(const std::string& str) {
        mCityTown = str;
    }
    void setProvince(const std::string& str) {
        mProvince = str;
    }
    void setZip(const std::string& str) {
        mZIP = str;
    }
    // Getters
    const std::string& line1() const {
        return mLine1;
    }
    const std::string& line2() const {
        return mLine2;
    }
    const std::string& cityTown() const {
        return mCityTown;
    }
    const std::string& province() const {
        return mProvince;
    }
    const std::string& zip() const {
        return mZIP;
    }

 private:
    std::string mLine1;
    std::string mLine2;
    std::string mCityTown;
    std::string mProvince;
    std::string mZIP;
};

}  // namespace entity
#endif  // CORE_ENTITY_ADDRESS_HPP_