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
#include "dashboarddata.hpp"
#include <algorithm>
#include <vector>
#include <storage/stackdb.hpp>

namespace dataprovider {
namespace dashboard {

entity::User DashboardDataProvider::getUserByID(const std::string& userID) {
    const entity::User user = [userID]() {
        for (const db::StackDB::UserTableItem& temp : DATABASE().SELECT_USERS_TABLE()) {
            if (temp.userID == userID) {
                return entity::User(temp.userID, temp.role, temp.PIN, temp.employeeID);
            }
        }
        // Return empty if not found
        return entity::User();
    }();
    return user;
}

entity::Employee DashboardDataProvider::getEmployeeInformation(const std::string& employeeID) {
    for (const db::StackDB::EmployeeTableItem &temp : DATABASE().SELECT_EMPLOYEES_TABLE()) {
        if (temp.employeeID == employeeID) {
            entity::Employee foundUser(
                temp.employeeID,
                temp.firstname,
                temp.middlename,
                temp.lastname,
                temp.birthdate,
                temp.gender,
                temp.position);
            // Get Address
            [&foundUser]() {
                const std::vector<db::StackDB::AddressTableItem>::iterator it =
                    std::find_if(DATABASE().SELECT_ADDRESS_TABLE().begin(),
                                 DATABASE().SELECT_ADDRESS_TABLE().end(),
                                 [&foundUser](const db::StackDB::AddressTableItem &e) {
                                     return e.ID == foundUser.employeeID();
                                 });
                if (it != DATABASE().SELECT_ADDRESS_TABLE().end()) {
                    foundUser.setAddress({
                        it->housenumber,
                        it->lot,
                        it->block,
                        it->subdivision,
                        it->sitio,
                        it->purok,
                        it->barangay,
                        it->city_town,
                        it->province,
                        it->zip,
                    });
                }
            }();
            // Get Contact details
            [&foundUser]() {
                const std::vector<db::StackDB::ContactDetailsTableItem>::iterator it =
                    std::find_if(DATABASE().SELECT_CONTACTS_TABLE().begin(),
                                 DATABASE().SELECT_CONTACTS_TABLE().end(),
                                 [&foundUser](const db::StackDB::ContactDetailsTableItem &e) {
                                     return e.ID == foundUser.employeeID();
                                 });
                if (it != DATABASE().SELECT_CONTACTS_TABLE().end()) {
                    foundUser.setPhoneNumbers(it->phone_number_1, it->phone_number_2);
                    foundUser.setEmail(it->email);
                }
            }();
            // Get personal IDs
            [&foundUser]() {
                for (const db::StackDB::PersonalIdTableItem& e : DATABASE().SELECT_PERSONAL_ID_TABLE()) {
                    if (e.ID == foundUser.employeeID()) {
                        foundUser.addPersonalId(e.id_number, e.id_number);
                    }
                }
            }();
            return foundUser;
        }
    }
    // Return empty if not found
    return entity::Employee();
}

}  // namespace dashboard
}  // namespace dataprovider