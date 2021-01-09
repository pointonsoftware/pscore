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
#include "customerdata.hpp"
#include <algorithm>
#include <string>
#include <vector>
#include <storage/stackdb.hpp>

namespace dataprovider {
namespace customermgmt {

std::vector<entity::Customer> CustomerDataProvider::getCustomers() {
    // SELECT Customers
    std::vector<entity::Customer> customers;
    for (const db::StackDB::CustomerTableItem& temp : DATABASE().SELECT_CUSTOMER_TABLE()) {
        entity::Customer customer(
            temp.customerID,
            temp.firstname,
            temp.middlename,
            temp.lastname,
            temp.birthdate,
            temp.gender);
        fillOtherDetails(&customer);
        customers.emplace_back(customer);
    }
    return customers;
}

void CustomerDataProvider::create(const entity::Customer& customer) {
    // Empty for now
}

void CustomerDataProvider::update(const entity::Customer& customer) {
    // Empty for now
}

void CustomerDataProvider::remove(const std::string& id) {
    // Empty for now
}

void CustomerDataProvider::fillOtherDetails(entity::Customer* customer) const {
        // Get Address
        [&customer]() {
            const std::vector<db::StackDB::AddressTableItem>::iterator it =
                    std::find_if(DATABASE().SELECT_ADDRESS_TABLE().begin(),
                            DATABASE().SELECT_ADDRESS_TABLE().end(),
                            [&customer](const db::StackDB::AddressTableItem& e) {
                               return e.ID == customer->ID();
                            });
            if (it != DATABASE().SELECT_ADDRESS_TABLE().end()) {
                customer->setAddress({
                    it->line1,
                    it->line2,
                    it->city_town,
                    it->province,
                    it->zip,
                });
            }
        }();
        // Get Contact details
        [&customer]() {
            const std::vector<db::StackDB::ContactDetailsTableItem>::iterator it =
                    std::find_if(DATABASE().SELECT_CONTACTS_TABLE().begin(),
                                DATABASE().SELECT_CONTACTS_TABLE().end(),
                                [&customer](const db::StackDB::ContactDetailsTableItem& e) {
                                    return e.ID == customer->ID();
                                });
            if (it != DATABASE().SELECT_CONTACTS_TABLE().end()) {
                customer->setPhoneNumbers(it->phone_number_1, it->phone_number_2);
                customer->setEmail(it->email);
            }
        }();
        // Get personal IDs
        [&customer]() {
            for (const db::StackDB::PersonalIdTableItem& e :
                 DATABASE().SELECT_PERSONAL_ID_TABLE()) {
                if (e.ID == customer->ID()) {
                    customer->addPersonalId(e.type, e.id_number);
                }
            }
        }();
}

}  // namespace customermgmt
}  // namespace dataprovider

