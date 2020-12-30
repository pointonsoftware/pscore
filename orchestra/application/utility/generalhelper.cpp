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

namespace app {
namespace utility {

/**
 * Code based-from StackOverflow by Galik
 * Author profile: https://stackoverflow.com/users/3807729/galik
 *
 * Original question: https://stackoverflow.com/q/38034033/3975468
 * Answer: https://stackoverflow.com/a/38034148/3975468
*/
std::string getDateTime() {
    typedef std::chrono::system_clock Clock;
    auto now = Clock::now();
    std::time_t now_c = Clock::to_time_t(now);
    std::tm bt {};
#ifdef __unix__
    localtime_r(&now_c, &bt);
#elif __WIN32__
    localtime_s(&bt, &now_c);
#else
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    bt = *std::localtime(&now_c);
#endif
    char buff[100];
    snprintf(buff, sizeof(buff), "%04u-%02u-%02u %02u:%02u:%02u", bt.tm_year + 1900,
                bt.tm_mon + 1, bt.tm_mday, bt.tm_hour, bt.tm_min, bt.tm_sec);
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
    return getDateTime().substr(2, 2) + std::to_string(randomNumber(10000, 99999));
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

}  // namespace utility
}  // namespace app