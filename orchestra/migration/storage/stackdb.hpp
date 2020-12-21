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

class StackDB {
 public:
    ~StackDB() = default;

    static StackDB& getDbInstance() {
        static StackDB instance;
        return instance;
    }

    struct EmployeeTableItem {
        std::string employeeID;
        std::string firstname;
        std::string middlename;
        std::string lastname;
        std::string birthdate;
        std::string gender;
        std::string position;
        std::string status;
        bool isSystemUser;
    };

    struct UserTableItem {
        std::string userID;
        std::string role;
        std::string PIN;
        std::string createdAt;
        std::string employeeID;  // Links to Employee ID
    };

    struct AddressTableItem {
        std::string ID;  // Links to person's ID
        std::string line1;
        std::string line2;
        std::string city_town;
        std::string province;
        std::string zip;
    };

    struct ContactDetailsTableItem {
        std::string ID;  // Links to person's ID
        std::string email;
        std::string phone_number_1;
        std::string phone_number_2;
    };

    struct PersonalIdTableItem {
        std::string ID;  // Links to person's ID
        std::string type;
        std::string id_number;
    };

    struct ProductTableItem {
        std::string sku;
        std::string name;
        std::string description;
        std::string barcode;
        std::string category;
        std::string brand;
        std::string uom;
        std::string stock;
        std::string status;
        std::string original_price;
        std::string sell_price;
        std::string supplier_name;
        std::string supplier_code;
    };

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

 private:
    StackDB();
    // employees storage
    static std::vector<EmployeeTableItem> EMPLOYEES_TABLE;
    // employees storage
    static std::vector<UserTableItem> USERS_TABLE;
    // address storage - of all persons
    static std::vector<AddressTableItem> ADDRESS_TABLE;
    // contacts storage - of all persons
    static std::vector<ContactDetailsTableItem> CONTACTS_TABLE;
    // personal ID storage - of all persons
    static std::vector<PersonalIdTableItem> PERSONAL_ID_TABLE;
    // product storage
    static std::vector<ProductTableItem> PRODUCT_TABLE;
    void populateEmployees();
    void populateProducts();
};

}  // namespace db
}  // namespace dataprovider
#endif  // ORCHESTRA_MIGRATION_STORAGE_STACKDB_HPP_