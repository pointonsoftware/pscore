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
#include "filelog.hpp"
#include <iomanip>
#include <sstream>

namespace utility {

constexpr char LOG_FILE_NAME[] = "syscore.log";

FileLogger::FileLogger() : mFileIo(LOG_FILE_NAME) {
    std::stringstream ss;
    ss << "+" << std::string(146, '-') << "+" << std::endl;
    ss << "|" << std::string(62, ' ')
              << "PSCORE FileLogger v1.0"
              << std::string(62, ' ') << "|"
              << std::endl;
    ss << "|" << std::string(63, ' ')
              << "(c) Pointon Software"
              << std::string(63, ' ') << "|"
              << std::endl;
    ss << "+" << std::string(146, '-') << "+" << std::endl;
    ss << "|" << std::string(50, ' ')
              << "Date/Time captured: [2020-12-11 22:01:22.397]"
              << std::string(51, ' ') << "|"
              << std::endl;
    ss << "+" << std::string(146, '-') << "+" << std::endl;
    mFileIo.write(ss.str());
}

void FileLogger::write(const std::string& logMode, const std::string& className,
               const std::string& methodName, const std::string& logString) {
    std::stringstream ss;
    ss << getTimestamp() << std::left << " | "
       << std::setw(MAX_CLASS_NAME_SIZE) << className  << " | "
       << std::setw(MAX_FUNC_NAME_SIZE)  << methodName << " |-- "
       << logString;
    mFileIo.write(ss.str());
}

FileLogger::~FileLogger() {
    std::stringstream ss;
    ss << getTimestamp() << std::left << " | -- System ShutDown";
    mFileIo.write(ss.str());
}

}  // namespace utility