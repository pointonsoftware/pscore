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
#include <string>
#include <algorithm>
#include <vector>
#include <storage/stackdb.hpp>

namespace dataprovider {
namespace dashboard {

entity::User DashboardDataProvider::getUserByID(const std::string& userID) {
    const entity::User user = [userID]() {
        for (const db::UserTableItem& temp : DATABASE().SELECT_USERS_TABLE()) {
            if (temp.userID == userID) {
                return entity::User(temp.userID, temp.role, temp.PIN,
                                    temp.createdAt, temp.employeeID);
            }
        }
        // Return empty if not found
        return entity::User();
    }();
    return user;
}

entity::Employee DashboardDataProvider::getEmployeeInformation(const std::string& employeeID) {
    for (const db::EmployeeTableItem &temp : DATABASE().SELECT_EMPLOYEES_TABLE()) {
        if (temp.employeeID == employeeID) {
            entity::Employee employee(
                temp.employeeID,
                temp.firstname,
                temp.middlename,
                temp.lastname,
                temp.birthdate,
                temp.gender,
                temp.position,
                temp.status,
                temp.isSystemUser);
            // Get Address
            [&employee]() {
                const std::vector<db::AddressTableItem>::iterator it =
                    std::find_if(DATABASE().SELECT_ADDRESS_TABLE().begin(),
                                 DATABASE().SELECT_ADDRESS_TABLE().end(),
                                 [&employee](const db::AddressTableItem &e) {
                                     return e.ID == employee.ID();
                                 });
                if (it != DATABASE().SELECT_ADDRESS_TABLE().end()) {
                    employee.setAddress({
                        it->line1,
                        it->line2,
                        it->city_town,
                        it->province,
                        it->zip,
                    });
                }
            }();
            // Get Contact details
            [&employee]() {
                const std::vector<db::ContactDetailsTableItem>::iterator it =
                    std::find_if(DATABASE().SELECT_CONTACTS_TABLE().begin(),
                                 DATABASE().SELECT_CONTACTS_TABLE().end(),
                                 [&employee](const db::ContactDetailsTableItem &e) {
                                     return e.ID == employee.ID();
                                 });
                if (it != DATABASE().SELECT_CONTACTS_TABLE().end()) {
                    employee.setPhoneNumbers(it->phone_number_1, it->phone_number_2);
                    employee.setEmail(it->email);
                }
            }();
            // Get personal IDs
            [&employee]() {
                for (const db::PersonalIdTableItem& e :
                     DATABASE().SELECT_PERSONAL_ID_TABLE()) {
                    if (e.ID == employee.ID()) {
                        employee.addPersonalId(e.type, e.id_number);
                    }
                }
            }();
            return employee;
        }
    }
    // Return empty if not found
    return entity::Employee();
}

}  // namespace dashboard
}  // namespace dataprovider