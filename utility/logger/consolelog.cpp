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
#include "consolelog.hpp"
#include <iostream>
#include <iomanip>

namespace utility {

#ifdef _WIN32
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
// https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
bool enableVTMode() {
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) {
        std::cout << "VT processing: INVALID_HANDLE_VALUE." << std::endl;
        return false;
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) {
        std::cout << "VT processing: GetConsoleMode failed." << std::endl;
        return false;
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) {
        std::cout << "VT processing: SetConsoleMode failed." << std::endl;
        return false;
    }
    return true;
}
#endif

void ConsoleLogger::write(const std::string& logMode, const std::string& className,
                           const std::string& methodName, const std::string& logString) {
#ifdef _WIN32
    // For Windows, we need to enable Console Virtual Terminal Processing
    // for the coloring to take effect
    if (!enableVTMode()) {
        std::cout << "Unable to enter VT processing mode." << std::endl;
    }
#endif
    // [2020-08-30 02:46:10.824] | SomeClass | SomeFunc |-- Hello World!
    std::cout << getLogModeTerminalColor(logMode)
              << getTimestamp() << std::left << " | "
              << std::setw(MAX_NAME)  << className  << " | "
              << std::setw(MAX_NAME)  << methodName << " | -- "
              << logString << "\033[0m"<< std::endl;
}

}  // namespace utility