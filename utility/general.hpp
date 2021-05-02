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
#ifndef UTILITY_GENERAL_HPP_
#define UTILITY_GENERAL_HPP_
#include <chrono>
#include <iomanip>
#include <sstream>
#include <string>
#include <type_traits>

namespace utility {
/*!
 * Checks if the string argument is a number
*/
extern bool isNumber(const std::string& str);
/*!
 * Checks if the string argument is a valid double
*/
extern bool isDouble(const std::string& str);
/*!
 * Checks if the string argument contains a number
*/
extern bool hasNumber(const std::string& str);
/*!
 * Returns the uppercase string equivalent
*/
extern std::string toUpper(std::string str);
/*!
 * Returns the lowercase string equivalent
*/
extern std::string toLower(std::string str);
/*!
 * Returns converted value if str is valid; returns zero otherwise
*/
extern double toDouble(const std::string& str);
/*!
 * Returns converted value
*/
template <typename T>
std::string toString(const T& value) {
    std::stringstream stream;
    if (std::is_same<T, double>::value || std::is_same<T, float>::value) {
        stream << std::fixed << std::setprecision(2) << value;
    } else {
        stream << value;
    }
    return stream.str();
}
/*!
 * Generates random integer from inclusive-range [low : high]
*/
extern unsigned int randomNumber(unsigned int low, unsigned int high);
}  // namespace utility

#endif  // UTILITY_GENERAL_HPP_