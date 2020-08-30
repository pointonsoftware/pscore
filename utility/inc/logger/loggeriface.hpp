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
    virtual void write(const std::string& className, const std::string& methodName,
                       const std::string& logString) = 0;
      virtual ~LoggerInterface()= default;
 protected:
    /**
    * Code copy-pasted from StackOverflow by bames53
    * Author profile: https://stackoverflow.com/users/365496/bames53
    * 
    * Original question: https://stackoverflow.com/q/27136854
    * Answer: https://stackoverflow.com/a/27137475
    */
    template <typename Duration>
    void printTime(tm t, Duration fraction) {
        using namespace std::chrono;
        std::printf("[%04u-%02u-%02u %02u:%02u:%02u.%03u]", t.tm_year + 1900,
                    t.tm_mon + 1, t.tm_mday, t.tm_hour, t.tm_min, t.tm_sec,
                    static_cast<unsigned>(duration_cast<milliseconds>(fraction).count()));
    }
    /**
    * Code copy-pasted from StackOverflow by bames53
    * Author profile: https://stackoverflow.com/users/365496/bames53
    * 
    * Original question: https://stackoverflow.com/q/27136854
    * Answer: https://stackoverflow.com/a/27137475
    */
    inline void getTime() {
        using namespace std;
        using namespace std::chrono;
        system_clock::time_point now = system_clock::now();
        system_clock::duration tp = now.time_since_epoch();
        tp -= duration_cast<seconds>(tp);
        time_t tt = system_clock::to_time_t(now);
        printTime(*localtime(&tt), tp);
    }
};
}  // namespace utility
#endif  // UTILITY_INC_LOGGER_LOGGERIFACE_HPP_