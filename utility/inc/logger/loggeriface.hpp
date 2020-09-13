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
#ifndef UTILITY_INC_LOGGER_LOGGERIFACE_HPP_
#define UTILITY_INC_LOGGER_LOGGERIFACE_HPP_

#include <ctime>
#include <chrono>
#include <iostream>
#include <string>

namespace utility {

constexpr unsigned int MIN_CHAR = 1;
constexpr unsigned int MAX_NAME = 20;

class LoggerInterface {
 public:
    virtual void write(const std::string& logMode, const std::string& className,
                       const std::string& methodName, const std::string& logString) = 0;
    virtual ~LoggerInterface()= default;

 protected:
    /**
    * Code based-from StackOverflow by bames53
    * Author profile: https://stackoverflow.com/users/365496/bames53
    * 
    * Original question: https://stackoverflow.com/q/27136854
    * Answer: https://stackoverflow.com/a/27137475
    */
    template <typename Duration>
    std::string formatTimestamp(tm t, Duration fraction) {
        using std::chrono::milliseconds;
        using std::chrono::duration_cast;
        char buff[100];
        snprintf(buff, sizeof(buff), "[%04u-%02u-%02u %02u:%02u:%02u.%03u]", t.tm_year + 1900,
                    t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec,
                    static_cast<unsigned>(duration_cast<milliseconds>(fraction).count()));
        return buff;
    }

    std::string getTimestamp();
    std::string getLogModeTerminalColor(const std::string& logMode);
};
}  // namespace utility
#endif  // UTILITY_INC_LOGGER_LOGGERIFACE_HPP_