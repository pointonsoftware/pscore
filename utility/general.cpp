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
#include "general.hpp"
#include <algorithm>
#include <chrono>
#include <mutex>
#include <random>

namespace utility {

bool isNumber(const std::string &str) {
  return !str.empty() && std::all_of(str.begin(), str.end(), ::isdigit);
}

bool isDouble(const std::string& str) {
    char* end = nullptr;
    double val = strtod(str.c_str(), &end);
    return end != str.c_str() && *end == '\0' && val != 999999;
}

bool hasNumber(const std::string &str) {
  return std::find_if(str.begin(), str.end(),
        [](unsigned char c) { return std::isdigit(c); }) != str.end();
}

std::string toUpper(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c){ return std::toupper(c); });
    return str;
}

std::string toLower(std::string str) {
    std::transform(str.begin(), str.end(), str.begin(),
                   [](unsigned char c){ return std::tolower(c); });
    return str;
}

double toDouble(const std::string& str) {
    return isDouble(str) ? strtod(str.c_str(), nullptr) : 0;
}

unsigned randomNumber(unsigned int low, unsigned int high) {
    std::random_device dev;
    std::mt19937 rng(dev());
    // low = 0 ; high = 9  -  generates number for 0 to 9
    std::uniform_int_distribution<std::mt19937::result_type> dist6(low, high);
    return dist6(rng);
}

/**
 * Code based-from StackOverflow by Galik
 * Author profile: https://stackoverflow.com/users/3807729/galik
 *
 * Original question: https://stackoverflow.com/q/38034033/3975468
 * Answer: https://stackoverflow.com/a/38034148/3975468
*/
std::tm currentDateTime() {
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
    return bt;
}

std::string currentDateTimeStr() {
    const std::tm& bt = currentDateTime();
    char buff[100];
    snprintf(buff, sizeof(buff), "%04u-%02u-%02u %02u:%02u:%02u", bt.tm_year + 1900,
                bt.tm_mon + 1, bt.tm_mday, bt.tm_hour, bt.tm_min, bt.tm_sec);
    return std::string(buff);
}

}  // namespace utility