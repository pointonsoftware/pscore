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
#include "stackdb.hpp"

namespace dataprovider {
namespace db {

std::vector<entity::User> StackDB::usersList;

StackDB::StackDB() {
    // If you want to add a user to our in-memory DB, put it here
    usersList.emplace_back(
            entity::User("Ben", "H", "Garcia", "10/15/2020", "Male", "10001", "Admin", "2020"));
    usersList.emplace_back(
            entity::User("Foo", "B", "Bar", "01/01/2020", "Male", "10002", "Manager", "1251"));
}

}  // namespace db
}  // namespace dataprovider