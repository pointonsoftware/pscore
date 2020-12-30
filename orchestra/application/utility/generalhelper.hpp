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
#ifndef ORCHESTRA_APPLICATION_UTILITY_GENERALHELPER_HPP_
#define ORCHESTRA_APPLICATION_UTILITY_GENERALHELPER_HPP_
#include <map>
#include <string>
#include <vector>

namespace app {
namespace util {
/*!
 * Generates an employee ID
 * ID format - [YY][unique-five-digit-number]
 * e.g. - 2021135
*/
extern std::string generateEmployeeID();
/*!
 * Returns a vector of map keys
*/
extern std::vector<std::string> extractMapKeys(const std::map<std::string, std::string>& map);
/*!
 * Returns a vector of map values
*/
extern std::vector<std::string> extractMapValues(const std::map<std::string, std::string>& map);
}  // namespace util
}  // namespace app
#endif  // ORCHESTRA_APPLICATION_UTILITY_GENERALHELPER_HPP_
