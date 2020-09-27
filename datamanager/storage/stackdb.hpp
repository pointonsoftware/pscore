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
#ifndef DATAMANAGER_STORAGE_STACKDB_HPP_
#define DATAMANAGER_STORAGE_STACKDB_HPP_
#include <string>
#include <vector>

// entities
#include <entity/user.hpp>

#define DATABASE() dataprovider::db::StackDB::getDbInstance()

namespace dataprovider {
namespace db {

class StackDB {
 public:
    ~StackDB() = default;

    static StackDB& getDbInstance() {
        static StackDB instance;
        return instance;
    }

    inline std::vector<entity::User>& getUsersList() const {
        return usersList;
    }

 private:
    StackDB();
    // users storage
    static std::vector<entity::User> usersList;
};

}  // namespace db
}  // namespace dataprovider
#endif  // DATAMANAGER_STORAGE_STACKDB_HPP_