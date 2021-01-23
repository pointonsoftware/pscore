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
void CustomerDataProvider::writeOtherDetails(const entity::Customer& customer) const {
    DATABASE().SELECT_ADDRESS_TABLE().emplace_back(db::StackDB::AddressTableItem {
            customer.ID(),
            customer.address().line1(),
            customer.address().line2(),
            customer.address().cityTown(),
            customer.address().province(),
            customer.address().zip()});
    DATABASE().SELECT_CONTACTS_TABLE().emplace_back(db::StackDB::ContactDetailsTableItem {
            customer.ID(),
            customer.contactDetails().email(),
            customer.contactDetails().phone1(),
            customer.contactDetails().phone2()});
    for (unsigned int i = 0; i < customer.personalIds().size(); i++) {
        DATABASE().SELECT_PERSONAL_ID_TABLE().emplace_back(db::StackDB::PersonalIdTableItem {
                customer.ID(),
                customer.personalIds()[i].type(),
                customer.personalIds()[i].number()});
    }
}
void CustomerDataProvider::create(const entity::Customer& customer) {
    if (std::find_if(DATABASE().SELECT_CUSTOMER_TABLE().begin(),
                            DATABASE().SELECT_CUSTOMER_TABLE().end(),
                            [&customer](const db::StackDB::CustomerTableItem& c) {
                               return c.customerID == customer.ID();
                            }) != DATABASE().SELECT_CUSTOMER_TABLE().end()) {
        // If ID exists, don't proceed!
        return;
    }
    DATABASE().SELECT_CUSTOMER_TABLE().emplace_back(db::StackDB::CustomerTableItem {
            customer.ID(),
            customer.firstName(),
            customer.middleName(),
            customer.lastName(),
            customer.birthdate(),
            customer.gender()});

    writeOtherDetails(customer);
}

void CustomerDataProvider::update(const entity::Customer& customer) {
    // Updating customer basic info
    {
        std::vector<db::StackDB::CustomerTableItem>::iterator it =
            std::find_if(DATABASE().SELECT_CUSTOMER_TABLE().begin(),
                                    DATABASE().SELECT_CUSTOMER_TABLE().end(),
                                    [&customer](const db::StackDB::CustomerTableItem& c) {
                                        // We only match the customer ID for updating
                                        return c.customerID == customer.ID();
                                    });
        if (it == DATABASE().SELECT_CUSTOMER_TABLE().end()) {
            // Not found
            return;
        }
        // Actual update
        *it = db::StackDB::CustomerTableItem {
                customer.ID(),
                customer.firstName(),
                customer.middleName(),
                customer.lastName(),
                customer.birthdate(),
                customer.gender()};
    }
    // Updating customer address
    {
        std::vector<db::StackDB::AddressTableItem>::iterator it =
            std::find_if(DATABASE().SELECT_ADDRESS_TABLE().begin(),
                                    DATABASE().SELECT_ADDRESS_TABLE().end(),
                                    [&customer](const db::StackDB::AddressTableItem& e) {
                                        // We only match the ID for updating
                                        return e.ID == customer.ID();
                                    });
        if (it == DATABASE().SELECT_ADDRESS_TABLE().end()) {
            // Not found
            return;
        }
        // Actual update
        *it = db::StackDB::AddressTableItem {
            customer.ID(),
            customer.address().line1(),
            customer.address().line2(),
            customer.address().cityTown(),
            customer.address().province(),
            customer.address().zip()};
    }
    // Updating customer contacts
    {
        std::vector<db::StackDB::ContactDetailsTableItem>::iterator it =
            std::find_if(DATABASE().SELECT_CONTACTS_TABLE().begin(),
                                    DATABASE().SELECT_CONTACTS_TABLE().end(),
                                    [&customer](const db::StackDB::ContactDetailsTableItem& e) {
                                        // We only match the customer ID for updating
                                        return e.ID == customer.ID();
                                    });
        if (it == DATABASE().SELECT_CONTACTS_TABLE().end()) {
            // Not found
            return;
        }
        // Actual update
        *it = db::StackDB::ContactDetailsTableItem {
            customer.ID(),
            customer.contactDetails().email(),
            customer.contactDetails().phone1(),
            customer.contactDetails().phone2()};
    }
    // Updating customer personal ID
    {
        // Todo (code) - currently supports updating the first personal ID only
        std::vector<db::StackDB::PersonalIdTableItem>::iterator it =
            std::find_if(DATABASE().SELECT_PERSONAL_ID_TABLE().begin(),
                                    DATABASE().SELECT_PERSONAL_ID_TABLE().end(),
                                    [&customer](const db::StackDB::PersonalIdTableItem& e) {
                                        // We only match the customer ID for updating
                                        return e.ID == customer.ID();
                                    });
        if (it == DATABASE().SELECT_PERSONAL_ID_TABLE().end()) {
            // Not found
            return;
        }
        // Actual update
        *it = db::StackDB::PersonalIdTableItem {
                customer.ID(),
                customer.personalIds()[0].type(),
                customer.personalIds()[0].number()};
    }
}

void CustomerDataProvider::remove(const std::string& id) {
    // Delete customer
    DATABASE().SELECT_CUSTOMER_TABLE().erase(
        std::remove_if(DATABASE().SELECT_CUSTOMER_TABLE().begin(),
                    DATABASE().SELECT_CUSTOMER_TABLE().end(),
                    [&](const db::StackDB::CustomerTableItem& c) {
                        return c.customerID == id;
                    }),
        DATABASE().SELECT_CUSTOMER_TABLE().end());
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

