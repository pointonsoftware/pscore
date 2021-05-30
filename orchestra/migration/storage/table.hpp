/**************************************************************************************************
*                                            PSCORE                                               *
*                               Copyright (C) 2021 Pointon Software                               *
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
#ifndef ORCHESTRA_MIGRATION_STORAGE_TABLE_HPP_
#define ORCHESTRA_MIGRATION_STORAGE_TABLE_HPP_
#include <string>

namespace dataprovider {
namespace db {

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
    std::string barcode;
    std::string sku;
    std::string name;
    std::string description;
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

struct CustomerTableItem {
    std::string customerID;
    std::string firstname;
    std::string middlename;
    std::string lastname;
    std::string birthdate;
    std::string gender;
};

struct UOMTableItem {
    std::string ID;
    std::string unit_name;
    std::string abbreviation;
};

struct CategoryTableItem {
    std::string ID;
    std::string category_name;
};

struct SalesTableItem {
    std::string ID;
    std::string date_time;
    std::string subtotal;
    std::string taxable_amount;
    std::string vat;
    std::string discount;
    std::string total;
    std::string amount_paid;
    std::string payment_type;
    std::string change;
    std::string cashierID;
    std::string customerID;
};

struct SalesItemTableItem {
    std::string saleID;
    std::string productID;
    std::string product_name;
    std::string unit_price;
    std::string quantity;
    std::string total_price;
};

}  // namespace db
}  // namespace dataprovider
#endif  // ORCHESTRA_MIGRATION_STORAGE_TABLE_HPP_