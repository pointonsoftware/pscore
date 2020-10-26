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
#include "logindata.hpp"
#include <storage/stackdb.hpp>

namespace dataprovider {
namespace login {

entity::User LoginDataProvider::findUserByPin(const std::string& inputPin) {
    // SELECT * WHERE PIN = inputPin
    const entity::User user = [inputPin]() {
        for (const db::StackDB::EmployeeTableItem& temp : DATABASE().SELECT_EMPLOYEES_TABLE()) {
            if (temp.PIN == inputPin) {
                return entity::User("", "", "", "", "", temp.employeeID, temp.position, temp.PIN);
            }
        }
        return entity::User();
    }();
    return user;
}

}  // namespace login
}  // namespace dataprovider