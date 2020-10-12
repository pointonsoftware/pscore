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
#ifndef ORCHESTRA_APPLICATION_SCREEN_SCREENDEFINES_HPP_
#define ORCHESTRA_APPLICATION_SCREEN_SCREENDEFINES_HPP_

namespace screen {
namespace defines {

/*!
 * Add the new screens here
*/
enum class display {
    EXIT      = 0x000,
    LOGIN     = 0x101,
    DASHBOARD = 0x214
};

constexpr unsigned int SCREEN_WIDTH = 80;
constexpr unsigned int LABEL_WIDTH = 12;
constexpr char LABEL_BOUNDARY = ':';
constexpr char DELIMETER_COMMA = ',';
constexpr char DELIMETER_DASH = '-';

}  // namespace defines
}  // namespace screen

#endif  // ORCHESTRA_APPLICATION_SCREEN_SCREENDEFINES_HPP_