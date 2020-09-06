/**************************************************************************************************
*                      Copyright (C) Pointon Software - All Rights Reserved                       *
*                                                                                                 *
*             Unauthorized copying of this file via any medium is strictly prohibited             *
*                                  Proprietary and confidential                                   *
*                                                                                                 *
*                   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020                   *
*                                                                                                 *
**************************************************************************************************/
#include <logger/consolelog.hpp>
#include <sys/time.h>
#include <iostream>
#include <iomanip>

namespace utility {

void ConsoleLogger:: write(const std::string& logMode, const std::string& className,
                           const std::string& methodName, const std::string& logString) {
    // [2020-08-30 02:46:10.824] | SomeClass | SomeFunc |-- Hello World!
    std::cout << getLogModeTerminalColor(logMode)
              << getTimestamp() << std::left << " | "
              << std::setw(MAX_NAME)  << className  << " | "
              << std::setw(MAX_NAME)  << methodName << " | -- "
              << logString << std::endl;
}

std::string ConsoleLogger::getLogModeTerminalColor(const std::string& logMode) {
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