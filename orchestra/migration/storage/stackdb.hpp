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
#ifndef ORCHESTRA_MIGRATION_STORAGE_STACKDB_HPP_
#define ORCHESTRA_MIGRATION_STORAGE_STACKDB_HPP_
#include <string>
#include <vector>

// entities
#include <entity/employee.hpp>
#include <entity/user.hpp>

#define DATABASE() dataprovider::db::StackDB::getDbInstance()

namespace dataprovider {
namespace db {

/*!
 * Todo - https://pointon.atlassian.net/browse/PCOR-39
 * Mimic a database table
 * - Create a struct that represents each items of that table
 * - For queries, return a const reference vector of structs
*/
class StackDB {
 public:
    ~StackDB() = default;

    static StackDB& getDbInstance() {
        static StackDB instance;
        return instance;
    }

    inline std::vector<entity::Employee>& getEmployeesList() const {
        return employeesList;
    }

    inline std::vector<entity::User>& getUsersList() const {
        return usersList;
    }

 private:
    StackDB();
    // employees storage
    static std::vector<entity::Employee> employeesList;
    void populateEmployees();
    // users storage
    static std::vector<entity::User> usersList;
    void populateUsers();
};

}  // namespace db
}  // namespace dataprovider
#endif  // ORCHESTRA_MIGRATION_STORAGE_STACKDB_HPP_