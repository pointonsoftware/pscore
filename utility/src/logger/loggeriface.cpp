/**************************************************************************************************
*                      Copyright (C) Pointon Software - All Rights Reserved                       *
*                                                                                                 *
*             Unauthorized copying of this file via any medium is strictly prohibited             *
*                                  Proprietary and confidential                                   *
*                                                                                                 *
*                   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020                   *
*                                                                                                 *
**************************************************************************************************/
#include <logger/loggeriface.hpp>
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
    return formatTimestamp(*localtime(&tt), tp);  // NOLINT(runtime/threadsafe_fn)
}

}  // namespace utility