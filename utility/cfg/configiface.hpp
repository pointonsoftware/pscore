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
#ifndef UTILITY_INC_CFG_CONFIGIFACE_HPP_
#define UTILITY_INC_CFG_CONFIGIFACE_HPP_

#include <string>

namespace utility {

class ConfigIface {
 public:
    ConfigIface() = default;
    virtual ~ConfigIface() = default;

    /*! void set()
     * Will override value if key exists
     * Otherwise, will create new key + value
    */
    virtual void set(const std::string& key, const std::string& value) = 0;

    /*! std::string get()
     * Will get the value of the specified key
     * Will return the defaultValue if key does not exist
    */
    virtual std::string get(const std::string& key, const std::string& defaultValue) = 0;
};

}  // namespace utility
#endif  // UTILITY_INC_CFG_CONFIGIFACE_HPP_