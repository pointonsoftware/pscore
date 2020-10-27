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
#include "employeedata.hpp"
#include <algorithm>
#include <string>
#include <vector>
#include <storage/stackdb.hpp>

namespace dataprovider {
namespace empmgmt {

std::vector<entity::Employee> EmployeeDataProvider::getEmployees() {
    // SELECT UNION(employeestable, addresstable, contactstable, personalIDtable)
    std::vector<entity::Employee> employees;

    // Gather all employees
    for (const db::StackDB::EmployeeTableItem& temp : DATABASE().SELECT_EMPLOYEES_TABLE()) {
        entity::Employee employee(
                temp.firstname,
                temp.middlename,
                temp.lastname,
                temp.birthdate,
                temp.gender,
                temp.employeeID,
                temp.position);
        fillEmployeeDetails(&employee);
        employees.emplace_back(employee);
    }
    return employees;
}

void EmployeeDataProvider::create(const entity::Employee& employee) {
    if (std::find_if(DATABASE().SELECT_EMPLOYEES_TABLE().begin(),
                            DATABASE().SELECT_EMPLOYEES_TABLE().end(),
                            [&employee](const db::StackDB::EmployeeTableItem& e) {
                               return e.employeeID == employee.employeeID();
                            }) == DATABASE().SELECT_EMPLOYEES_TABLE().end()) {
        // If employee ID exists, don't proceed!
        return;
    }
    DATABASE().SELECT_EMPLOYEES_TABLE().emplace_back(db::StackDB::EmployeeTableItem {
            employee.employeeID(),
            employee.firstName(),
            employee.middleName(),
            employee.lastName(),
            employee.birthdate(),
            employee.gender(),
            employee.position(),
            ""});

    writeEmployeeDetails(employee);
}

void EmployeeDataProvider::create(const entity::User& user) {
    if (std::find_if(DATABASE().SELECT_EMPLOYEES_TABLE().begin(),
                            DATABASE().SELECT_EMPLOYEES_TABLE().end(),
                            [&user](const db::StackDB::EmployeeTableItem& e) {
                               return e.employeeID == user.employeeID();
                            }) == DATABASE().SELECT_EMPLOYEES_TABLE().end()) {
        // If employee ID exists, don't proceed!
        return;
    }
    DATABASE().SELECT_EMPLOYEES_TABLE().emplace_back(db::StackDB::EmployeeTableItem {
            user.employeeID(),
            user.firstName(),
            user.middleName(),
            user.lastName(),
            user.birthdate(),
            user.gender(),
            user.position(),
            user.pin()});

    writeEmployeeDetails(dynamic_cast<const entity::Employee&>(user));
}

void EmployeeDataProvider::writeEmployeeDetails(const entity::Employee& employee) const {
    DATABASE().SELECT_ADDRESS_TABLE().emplace_back(db::StackDB::AddressTableItem {
            employee.employeeID(),
            employee.address().housenumber,
            employee.address().lot,
            employee.address().block,
            employee.address().street,
            employee.address().subdivision,
            employee.address().sitio,
            employee.address().purok,
            employee.address().barangay,
            employee.address().city_town,
            employee.address().province,
            employee.address().zip});
    DATABASE().SELECT_CONTACTS_TABLE().emplace_back(db::StackDB::ContactDetailsTableItem {
            employee.employeeID(),
            employee.contactDetails().email,
            employee.contactDetails().phone_number[0]});
    for (unsigned int i = 0; i < employee.personalIds().size(); i++) {
        DATABASE().SELECT_PERSONAL_ID_TABLE().emplace_back(db::StackDB::PersonalIdTableItem {
                employee.employeeID(),
                employee.personalIds()[i].type,
                employee.personalIds()[i].id_number});
    }
}

void EmployeeDataProvider::removeWithID(const std::string& id) {
    // Delete in EMPLOYEES
    DATABASE().SELECT_EMPLOYEES_TABLE().erase(
        std::remove_if(DATABASE().SELECT_EMPLOYEES_TABLE().begin(),
                    DATABASE().SELECT_EMPLOYEES_TABLE().end(),
                    [&](const db::StackDB::EmployeeTableItem& e) {
                        return e.employeeID == id;
                    }),
        DATABASE().SELECT_EMPLOYEES_TABLE().end());
    // Delete the Address
    DATABASE().SELECT_ADDRESS_TABLE().erase(
        std::remove_if(DATABASE().SELECT_ADDRESS_TABLE().begin(),
                    DATABASE().SELECT_ADDRESS_TABLE().end(),
                    [&](const db::StackDB::AddressTableItem& e) {
                        return e.ID == id;
                    }),
        DATABASE().SELECT_ADDRESS_TABLE().end());
    // Delete the Contacts
    DATABASE().SELECT_CONTACTS_TABLE().erase(
        std::remove_if(DATABASE().SELECT_CONTACTS_TABLE().begin(),
                    DATABASE().SELECT_CONTACTS_TABLE().end(),
                    [&](const db::StackDB::ContactDetailsTableItem& e) {
                        return e.ID == id;
                    }),
        DATABASE().SELECT_CONTACTS_TABLE().end());
    // Delete the Personal ID
    DATABASE().SELECT_PERSONAL_ID_TABLE().erase(
        std::remove_if(DATABASE().SELECT_PERSONAL_ID_TABLE().begin(),
                    DATABASE().SELECT_PERSONAL_ID_TABLE().end(),
                    [&](const db::StackDB::PersonalIdTableItem& e) {
                        return e.ID == id;
                    }),
        DATABASE().SELECT_PERSONAL_ID_TABLE().end());
}

void EmployeeDataProvider::fillEmployeeDetails(entity::Employee* employee) const {
        // Get Address
        [&employee]() {
            const std::vector<db::StackDB::AddressTableItem>::iterator it =
                    std::find_if(DATABASE().SELECT_ADDRESS_TABLE().begin(),
                            DATABASE().SELECT_ADDRESS_TABLE().end(),
                            [&employee](const db::StackDB::AddressTableItem& e) {
                               return e.ID == employee->employeeID();
                            });
            if (it != DATABASE().SELECT_ADDRESS_TABLE().end()) {
                employee->setAddress({
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
        [&employee]() {
            const std::vector<db::StackDB::ContactDetailsTableItem>::iterator it =
                    std::find_if(DATABASE().SELECT_CONTACTS_TABLE().begin(),
                                DATABASE().SELECT_CONTACTS_TABLE().end(),
                                [&employee](const db::StackDB::ContactDetailsTableItem& e) {
                                    return e.ID == employee->employeeID();
                                });
            if (it != DATABASE().SELECT_CONTACTS_TABLE().end()) {
                employee->addPhoneNumber(it->phone_number);
                /*!
                 * Each user only have one email
                 * Hence we have this if-checking so the email is not overwritten with empty string
                */
                if (!it->email.empty()) {
                    employee->setEmail(it->email);
                }
            }
        }();
        // Get personal IDs
        [&employee]() {
            const std::vector<db::StackDB::PersonalIdTableItem>::iterator it =
                    std::find_if(DATABASE().SELECT_PERSONAL_ID_TABLE().begin(),
                                DATABASE().SELECT_PERSONAL_ID_TABLE().end(),
                                [&employee](const db::StackDB::PersonalIdTableItem& e) {
                                    return e.ID == employee->employeeID();
                                });
            if (it != DATABASE().SELECT_PERSONAL_ID_TABLE().end()) {
                employee->addPersonalId(it->type, it->id_number);
            }
        }();
}
}  // namespace empmgmt
}  // namespace dataprovider

