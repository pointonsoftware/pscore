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
#include "loggeriface.hpp"
#include <sys/time.h>
#include <iostream>
#include <iomanip>

namespace utility {

/**
 * Code based-from StackOverflow by bames53
 * Author profile: https://stackoverflow.com/users/365496/bames53
 * 
 * Original question: https://stackoverflow.com/q/27136854
 * Answer: https://stackoverflow.com/a/27137475
*/
std::string LoggerInterface::getTimestamp() {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    std::chrono::system_clock::duration tp = now.time_since_epoch();
    tp -= std::chrono::duration_cast<std::chrono::seconds>(tp);
    time_t tt = std::chrono::system_clock::to_time_t(now);
    std::tm bt {};
#if defined(__unix__)
    localtime_r(&tt, &bt);
#elif defined(_MSC_VER)
    localtime_s(&bt, &tt);
#else
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    bt = *std::localtime(&tt);
#endif
    return formatTimestamp(bt, tp);  // NOLINT(runtime/threadsafe_fn)
}

std::string LoggerInterface::getLogModeTerminalColor(const std::string& logMode) {
    if (logMode.compare("info") == 0) {
        return "\033[0;36m";
    }
    if (logMode.compare("warn") == 0) {
        return "\033[0;33m";
    }
    if (logMode.compare("error") == 0) {
        return "\033[0;31m";
    }
    return "";
}

}  // namespace utility