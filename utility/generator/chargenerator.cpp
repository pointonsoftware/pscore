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
#include "chargenerator.hpp"
#include <random>
#include <string>
#include <generalutils.hpp>

namespace utility {
namespace chargenerator {

std::string generateUID(const std::string& p1, const std::string& p2) {
    // first-letter-of-param1 + first-three-letters-of-param2 + three-digit-unique-number
    return toUpper(p1.at(0) + p2.substr(0, 2) + std::to_string(randomNumber(100, 999)));
}

std::string generateCustomerID(const std::string& p1, const std::string& p2) {
    // CM + first-letter-of-param1 + first-two-letters-of-param2 + 6-alphanumeric-chars
    return "CM" + toUpper(p1.at(0) + p2.substr(0, 2)) + generateChars(6);
}

/**
 * Code based-from StackOverflow by Galik
 * Author profile: https://stackoverflow.com/users/3807729/galik
 *
 * Original question: https://stackoverflow.com/q/440133/3975468
 * Answer: https://stackoverflow.com/a/24586587/3975468
*/
std::string generateChars(const uint8_t len) {
    static auto& chrs = "0123456789"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    thread_local static std::mt19937 rg {std::random_device {}()};
    thread_local static
        std::uniform_int_distribution<std::string::size_type> pick(0, sizeof(chrs) - 2);

    std::string temp;
    temp.reserve(len);
    for (int i = 0; i < len; ++i) {
        temp += chrs[pick(rg)];
    }
    return temp;
}

}  // namespace chargenerator
}  // namespace utility