/**************************************************************************************************
*                      Copyright (C) Pointon Software - All Rights Reserved                       *
*                                                                                                 *
*             Unauthorized copying of this file via any medium is strictly prohibited             *
*                                  Proprietary and confidential                                   *
*                                                                                                 *
*                   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020                   *
*                                                                                                 *
**************************************************************************************************/
#ifndef UTILITY_INC_LOGGER_CONSOLELOG_HPP_
#define UTILITY_INC_LOGGER_CONSOLELOG_HPP_

#include <string>
#include "loggeriface.hpp"

namespace utility {

class ConsoleLogger : public LoggerInterface {
 private:
    /**
    * Code copy-pasted from StackOverflow by bames53
    * Author profile: https://stackoverflow.com/users/365496/bames53
    *
    * Original question: https://stackoverflow.com/q/27136854
    * Answer: https://stackoverflow.com/a/27137475
    */
    template <typename Duration>
    void printTime(tm t, Duration fraction) {
        using std::chrono::milliseconds;
        using std::chrono::duration_cast;
        std::printf("[%04u-%02u-%02u %02u:%02u:%02u.%03u]", t.tm_year + 1900,
                    t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec,
                    static_cast<unsigned>(duration_cast<milliseconds>(fraction).count()));
    }

    void write(const std::string& logMode, const std::string& className,
               const std::string& methodName, const std::string& logString) override;
    std::string getLogModeTerminalColor(const std::string& logMode);
};

}  // namespace utility
#endif  // UTILITY_INC_LOGGER_CONSOLELOG_HPP_