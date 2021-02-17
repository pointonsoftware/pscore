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
#include "table.hpp"

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

    inline std::vector<EmployeeTableItem>& SELECT_EMPLOYEES_TABLE() const {
        return EMPLOYEES_TABLE;
    }

    inline std::vector<UserTableItem>& SELECT_USERS_TABLE() const {
        return USERS_TABLE;
    }

    inline std::vector<AddressTableItem>& SELECT_ADDRESS_TABLE() const {
        return ADDRESS_TABLE;
    }

    inline std::vector<ContactDetailsTableItem>& SELECT_CONTACTS_TABLE() const {
        return CONTACTS_TABLE;
    }

    inline std::vector<PersonalIdTableItem>& SELECT_PERSONAL_ID_TABLE() const {
        return PERSONAL_ID_TABLE;
    }

    inline std::vector<ProductTableItem>& SELECT_PRODUCT_TABLE() const {
        return PRODUCT_TABLE;
    }

    inline std::vector<CustomerTableItem>& SELECT_CUSTOMER_TABLE() const {
        return CUSTOMER_TABLE;
    }

    inline std::vector<UOMTableItem>& SELECT_UOM_TABLE() const {
        return UOM_TABLE;
    }

    inline std::vector<SalesTableItem>& SELECT_SALES_TABLE() const {
        return SALES_TABLE;
    }

    inline std::vector<SalesItemTableItem>& SELECT_SALES_ITEM_TABLE() const {
        return SALES_ITEM_TABLE;
    }

 private:
    StackDB();
    // employees storage
    static std::vector<EmployeeTableItem> EMPLOYEES_TABLE;
    // users storage
    static std::vector<UserTableItem> USERS_TABLE;
    // address storage - of all persons
    static std::vector<AddressTableItem> ADDRESS_TABLE;
    // contacts storage - of all persons
    static std::vector<ContactDetailsTableItem> CONTACTS_TABLE;
    // personal ID storage - of all persons
    static std::vector<PersonalIdTableItem> PERSONAL_ID_TABLE;
    // product storage
    static std::vector<ProductTableItem> PRODUCT_TABLE;
    // customer storage
    static std::vector<CustomerTableItem> CUSTOMER_TABLE;
    // unit of measurement storage
    static std::vector<UOMTableItem> UOM_TABLE;
    // sales storage
    static std::vector<SalesTableItem> SALES_TABLE;
    // sales item storage
    static std::vector<SalesItemTableItem> SALES_ITEM_TABLE;

    void populateEmployees();
    void populateProducts();
    void populateCustomers();
    void populateUOM();
    void populateSales();
};

}  // namespace db
}  // namespace dataprovider
#endif  // ORCHESTRA_MIGRATION_STORAGE_STACKDB_HPP_