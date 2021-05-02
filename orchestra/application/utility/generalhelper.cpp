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
#include "generalhelper.hpp"
#include <algorithm>
#include <chrono>
#include <ctime>
#include <mutex>
#include <random>
#include <string>
#include <datetime/datetime.hpp>
#include <general.hpp>  // pscore utility

namespace app {
namespace util {

std::string generateEmployeeID() {
    // Substring the last two digit of the year + unique_number
    return utility::currentDateTimeStr().substr(2, 2) +
           std::to_string(utility::randomNumber(10000, 99999));
}

std::vector<std::string> extractMapKeys(const std::map<std::string, std::string>& map) {
    std::vector<std::string> temp;
    for (auto const &key : map) {
        temp.emplace_back(key.first);
    }
    return temp;
}

std::vector<std::string> extractMapValues(const std::map<std::string, std::string>& map) {
    std::vector<std::string> temp;
    for (auto const &value : map) {
        temp.emplace_back(value.second);
    }
    return temp;
}

}  // namespace util
}  // namespace app