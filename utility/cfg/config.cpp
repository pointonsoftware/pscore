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
#include <algorithm>
#include <string>
#include <cfg/config.hpp>

namespace utility {

constexpr char EQUALS_SIGN[] = "=";
constexpr int OFFSET_ONE = 1;

Config::Config(const std::string& fileName) : mFileIo(fileName) {
    // Empty for now
}

void Config::set(const std::string& key, const std::string& value) {
    const std::string updateLine = key + EQUALS_SIGN + value;
    if (getLineFromConfig(key).empty()) {
        mFileIo.write(updateLine);
    } else {
        mFileIo.find_and_replace(key, updateLine);
    }
}

std::string Config::get(const std::string& key, const std::string& defaultValue) {
    const std::string line = getLineFromConfig(key);
    if (line.empty()) {
        return defaultValue;
    }
    return extractValueFromLine(line);
}

std::string Config::extractValueFromLine(const std::string& line) {
    return line.substr(line.find(EQUALS_SIGN) + OFFSET_ONE);
}

std::string Config::getLineFromConfig(const std::string& key) {
    std::string templine;
    mFileIo.find(key, &templine);
    // templine is empty if mFileIo.find operation is not successful (see above)
    return templine;
}

}  // namespace utility
