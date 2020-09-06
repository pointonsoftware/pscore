/**************************************************************************************************
*                      Copyright (C) Pointon Software - All Rights Reserved                       *
*                                                                                                 *
*             Unauthorized copying of this file via any medium is strictly prohibited             *
*                                  Proprietary and confidential                                   *
*                                                                                                 *
*                   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020                   *
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
};
}  // namespace utility
#endif  // UTILITY_INC_LOGGER_LOGGERIFACE_HPP_