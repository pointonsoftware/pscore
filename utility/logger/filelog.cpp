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
#include <algorithm>
#include <iomanip>
#include <sstream>
#include <cfg/config.hpp>
#include <general.hpp>

namespace utility {

constexpr char LOG_FILE_NAME[] = "syscore.log";

FileLogger::FileLogger() : mFileIo(LOG_FILE_NAME) {
    prepareFile();
    printHeader();
}

void FileLogger::prepareFile() {
    /**
     * Summary: Check if last line contains "shutdown"
     * If not, it means the previous system run was aborted.
     *    Let's save the logs as another file with the last date
     * Then wipe out the old file.
     */
    bool isSavePreviousLog = [this] {
        const std::string lastLine = mFileIo.get_last_line();
        return !lastLine.empty() && lastLine.find("shutdown") == std::string::npos;
    }();

    if (isSavePreviousLog) {
        std::ifstream currentFile(LOG_FILE_NAME, std::ios::in);
        std::ofstream newFile(std::string("syscore_")
                              .append(extractTimeStamp(mFileIo.get_last_line())
                              .append(".log")),
                              std::ios::out);
        newFile << currentFile.rdbuf();
    }

    mFileIo.clear_contents();
}

void FileLogger::printHeader() {
    std::stringstream ss;
    ss << "+" << std::string(146, '-') << "+" << std::endl;
    {
        Config config("psinfo.cfg");
        ss << "|" << std::string(62, ' ')
                << "CORE "
                << config.get("version", "x.x.x")
                << " File Logger"
                << std::string(62, ' ') << "|"
                << std::endl;
    }
    ss << "|" << std::string(63, ' ')
              << "(c) Pointon Software"
              << std::string(63, ' ') << "|"
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

std::string FileLogger::extractTimeStamp(const std::string& str) {
    const size_t start = str.find("[");
    const size_t end = str.find(".");
    std::string dateTime = str.substr(start + 1, end - (start + 1));
    // from [2020-12-11 22:01:22.397] to 20201211_220122
    dateTime.erase(std::remove(dateTime.begin(), dateTime.end(), '-'), dateTime.end());
    dateTime.erase(std::remove(dateTime.begin(), dateTime.end(), ':'), dateTime.end());
    std::replace(dateTime.begin(), dateTime.end(), ' ', '_');
    return dateTime;
}

FileLogger::~FileLogger() {
    std::stringstream ss;
    ss << getTimestamp() << std::left << " | -- System shutdown";
    mFileIo.write(ss.str());
}

}  // namespace utility