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
#include <logger/consolelog.hpp>
#include <sys/time.h>
#include <iostream>
#include <iomanip>

namespace utility {

void ConsoleLogger::write(const std::string& logMode, const std::string& className,
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