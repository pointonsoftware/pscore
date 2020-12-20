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
#ifndef UTILITY_GENERATOR_CHARGENERATOR_HPP_
#define UTILITY_GENERATOR_CHARGENERATOR_HPP_
#include <string>

namespace utility {
namespace chargenerator {
/*!
 * Generates the system user ID
 * Format - [first-letter-of-param1][first-three-letters-of-param2][three-digit-unique-number]
 * e.g.
 * p1 = John
 * p2 = Doe
 * result = JDOE123
*/
extern std::string generateUID(const std::string& p1, const std::string& p2);
}  // namespace chargenerator
}  // namespace utility
#endif  // UTILITY_GENERATOR_CHARGENERATOR_HPP_
