/**************************************************************************************************
*                      Copyright (C) Pointon Software - All Rights Reserved                       *
*                                                                                                 *
*             Unauthorized copying of this file via any medium is strictly prohibited             *
*                                  Proprietary and confidential                                   *
*                                                                                                 *
*                   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020                   *
*                                                                                                 *
**************************************************************************************************/
#include "logger/consolelog.hpp"
#include <sys/time.h>
#include <iostream>
#include <iomanip>

namespace utility {

void ConsoleLogger::write(const std::string& className, const std::string& methodName,
                          const std::string& logString) {
    // [2020-08-30 02:46:10.824] | SomeClass | SomeFunc |- Hello World!
    getTime();
    std::cout << std::left << " | "
              << std::setw(MAX_NAME)  << className  << " | "
              << std::setw(MAX_NAME)  << methodName << " | -- "
              << logString << std::endl;
}

}  // namespace utility