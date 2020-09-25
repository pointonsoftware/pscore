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
#include "authdata.hpp"
#include <stackdb.hpp>

namespace dataprovider {
namespace authentication {

entity::User AuthDataProvider::findUserByPin(const std::string& inputPin) {
    const entity::User user = [inputPin]() {
        for (const entity::User& temp : DATABASE().getUsersList()) {
            if (temp.pin().find(inputPin) != std::string::npos) {
                return temp;
            }
        }
        return entity::User();
    }();
    return user;
}

}  // namespace authentication
}  // namespace dataprovider