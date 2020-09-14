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
#ifndef UTILITY_CFG_CONFIG_HPP_
#define UTILITY_CFG_CONFIG_HPP_

#include <string>
#include "configiface.hpp"
#include <fileio/fileio.hpp>

namespace utility {

class Config : public ConfigIface {
 public:
    explicit Config(const std::string& fileName);
    ~Config() = default;
    void set(const std::string& key, const std::string& value) override;
    std::string get(const std::string& key, const std::string& defaultValue) override;

 private:
    FileIo mFileIo;
    std::string getLineFromConfig(const std::string& key);
    std::string extractValueFromLine(const std::string& line);
};

}  // namespace utility
#endif  // UTILITY_CFG_CONFIG_HPP_