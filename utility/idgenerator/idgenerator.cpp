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
#include "idgenerator.hpp"
#include <algorithm>
#include <chrono>
#include <ctime>
#include <random>
#include <string>

namespace utility {
namespace IdGenerator {

std::string getDate() {
    typedef std::chrono::system_clock Clock;
    auto now = Clock::now();
    std::time_t now_c = Clock::to_time_t(now);
    struct tm *parts = std::localtime(&now_c);
    char buff[100];
    snprintf(buff, sizeof(buff), "%04u-%02u-%02u", parts->tm_year + 1900,
                  parts->tm_mon + 1, parts->tm_mday);
    return std::string(buff);
}

unsigned randomNumber(unsigned int low, unsigned int high) {
    std::random_device dev;
    std::mt19937 rng(dev());
    // low = 0 ; high = 9  -  generates number for 0 to 9
    std::uniform_int_distribution<std::mt19937::result_type> dist6(low, high);
    return dist6(rng);
}

std::string generateEmployeeID() {
    // Substring the last two digit of the year + unique_number
    return getDate().substr(2, 2) + std::to_string(randomNumber(10000, 99999));
}

std::string generateUID(const std::string& p1, const std::string& p2) {
    auto convertToUpperCase = [](std::string str) {
        std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c){ return std::toupper(c); });
        return str;
    };
    // first-letter-of-param1 + first-three-letters-of-param2 + three-digit-unique-number
    return convertToUpperCase(p1.at(0) + p2.substr(0, 2) + std::to_string(randomNumber(100, 999)));
}

}  // namespace IdGenerator
}  // namespace utility