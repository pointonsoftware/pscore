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

#include <string>

namespace utility {
/*!
 * Checks if the string argument is a number
*/
extern bool isNumber(const std::string& str);
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
 * Generates random integer from inclusive-range [low : high]
*/
extern unsigned int randomNumber(unsigned int low, unsigned int high);
/*!
 * Returns the current date-time in "dd/mm/yyyy HH:MM:SS" form
*/
extern std::string currentDateTime();
}  // namespace utility

#endif  // UTILITY_GENERAL_HPP_