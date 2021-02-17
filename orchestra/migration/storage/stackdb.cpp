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
#include "stackdb.hpp"

namespace dataprovider {
namespace db {

std::vector<EmployeeTableItem> StackDB::EMPLOYEES_TABLE;
std::vector<UserTableItem> StackDB::USERS_TABLE;
std::vector<AddressTableItem> StackDB::ADDRESS_TABLE;
std::vector<ContactDetailsTableItem> StackDB::CONTACTS_TABLE;
std::vector<PersonalIdTableItem> StackDB::PERSONAL_ID_TABLE;
std::vector<ProductTableItem> StackDB::PRODUCT_TABLE;
std::vector<CustomerTableItem> StackDB::CUSTOMER_TABLE;
std::vector<UOMTableItem> StackDB::UOM_TABLE;
std::vector<SalesTableItem> StackDB::SALES_TABLE;
std::vector<SalesItemTableItem> StackDB::SALES_ITEM_TABLE;

StackDB::StackDB() {
    // Admin user
    USERS_TABLE.emplace_back(UserTableItem {
            "2020202",                    // Unique User ID
            "Admin",                      // Role
            "1251",                       // PIN <!Unique> <!Empty if non-user>
            "2020/01/12 11:09:50",        // Created At
            ""});                         // No employee ID
    populateEmployees();
    populateProducts();
    populateCustomers();
    populateUOM();
}

void StackDB::populateEmployees() {
    // If you want to add a user/employee to our in-memory DB, put it here

    //------- Copy starting from the line below
    EMPLOYEES_TABLE.emplace_back(EmployeeTableItem {
            "2014566",                    // Employee ID <!Make sure this is unique>
            "BenZiv",                     // First name
            "Hero",                       // Middle name
            "Garcia",                     // Last name
            "2020/10/15",                 // B-date
            "M",                          // Gender
            "Manager",                    // Position
            "ACTIVE",                     // Status - ACTIVE, ON-LEAVE or INACTIVE
            true});                       // System user
    USERS_TABLE.emplace_back(UserTableItem {
            "BGAR123",                    // User ID <!Make sure this is unique>
            "Manager",                    // Role
            "2020",                       // PIN
            "2020/01/10 07:47:48",        // Created At
            "2014566"});                  // Link to employee ID
    ADDRESS_TABLE.emplace_back(AddressTableItem {
            "2014566",                    // Employee ID <!Same as employeeID>
            "Lot 5, Blk 10, Petunia St",  // Line 1
            "Camella Homes, Basak",       // Line 2
            "Lapu-Lapu City",             // City/Town
            "Cebu",                       // Province
            "6015"});                     // ZIP
    CONTACTS_TABLE.emplace_back(ContactDetailsTableItem {
            "2014566",                    // Employee ID <!Same as employeeID>
            "test@gmail.com",             // Email
            "09123334567",                // Contact number 1
            "09987654321"});              // Contact number 2
    PERSONAL_ID_TABLE.emplace_back(PersonalIdTableItem {
            "2014566",                    // Employee ID <!Same as employeeID>
            "SSS",                        // Type
            "003-311-150-413"});          // ID-number
    PERSONAL_ID_TABLE.emplace_back(PersonalIdTableItem {
            "2014566",                    // Employee ID <!Must be the same as above>
            "UMID",                       // Type
            "04-1511167-8"});             // ID-number
    //------- End here

    //------- 2019542
    EMPLOYEES_TABLE.emplace_back(EmployeeTableItem {
            "2019542",                    // Employee ID <!Make sure this is unique>
            "Zandro",                     // First name
            "Slardar",                    // Middle name
            "Mage",                       // Last name
            "2020/10/10",                 // B-date
            "M",                          // Gender
            "Cashier",                    // Position
            "ACTIVE",                     // Status - ACTIVE, ON-LEAVE or INACTIVE
            true});                       // System user
    USERS_TABLE.emplace_back(UserTableItem {
            "BGAR567",                    // User ID <!Make sure this is unique>
            "Cashier",                    // Role
            "2021",                       // PIN
            "2020/10/02 08:47:48",        // Created At
            "2019542"});                  // Link to employee ID
    ADDRESS_TABLE.emplace_back(AddressTableItem {
            "2019542",                    // Employee ID <!Same as employeeID>
            "Bacbacan, San Francisco",    // Line 1
            "",                           // Line 2
            "Malayong Dapit",             // City/Town
            "Davao",                      // Province
            "6060"});                     // ZIP
    CONTACTS_TABLE.emplace_back(ContactDetailsTableItem {
            "2019542",                    // Employee ID <!Same as employeeID>
            "zznn@gmail.com",             // Email
            "09123334567",                // Contact number 1
            ""});                         // Contact number 2
    PERSONAL_ID_TABLE.emplace_back(PersonalIdTableItem {
            "2019542",                    // Employee ID <!Same as employeeID>
            "Driver's License",           // Type
            "N04-10-021355"});            // ID-number

    //------- 2098472
    EMPLOYEES_TABLE.emplace_back(EmployeeTableItem {
            "2098472",                    // Employee ID <!Make sure this is unique>
            "Juana",                      // First name
            "Santos",                     // Middle name
            "Dela Cruz",                  // Last name
            "2020/10/18",                 // B-date
            "F",                          // Gender
            "Cashier",                    // Position
            "ACTIVE",                     // Status - ACTIVE, ON-LEAVE or INACTIVE
            true});                       // System user
    USERS_TABLE.emplace_back(UserTableItem {
            "JDEL554",                    // User ID <!Make sure this is unique>
            "Cashier",                    // Role
            "2022",                       // PIN
            "2020/05/10 10:09:50",        // Created At
            "2098472"});                  // Link to employee ID
    ADDRESS_TABLE.emplace_back(AddressTableItem {
            "2098472",                    // Employee ID <!Same as employeeID>
            "BF Homes, Poblacion",        // Line 1
            "",                           // Line 2
            "Lapu-Lapu City",             // City/Town
            "Cebu",                       // Province
            "6015"});                     // ZIP
    CONTACTS_TABLE.emplace_back(ContactDetailsTableItem {
            "2098472",                    // Employee ID <!Same as employeeID>
            "juana@gmail.com",            // Email
            "09123334567",                // Contact number 1
            ""});                         // Contact number 2
    PERSONAL_ID_TABLE.emplace_back(PersonalIdTableItem {
            "2098472",                    // Employee ID <!Same as employeeID>
            "Driver's License",           // Type
            "N04-10-0215655"});           // ID-number

    //------- 2054993
    EMPLOYEES_TABLE.emplace_back(EmployeeTableItem {
            "2054993",                    // Employee ID <!Make sure this is unique>
            "Rodrigo",                    // First name
            "Roa",                        // Middle name
            "Duterte",                    // Last name
            "1977/10/17",                 // B-date
            "M",                          // Gender
            "Security Guard",             // Position
            "ACTIVE",                     // Status - ACTIVE, ON-LEAVE or INACTIVE
            false});                      // System user
    ADDRESS_TABLE.emplace_back(AddressTableItem {
            "2054993",                    // Employee ID <!Same as employeeID>
            "22 St. Andrews Hills",       // Line 1
            "Poblacion",                  // Line 2
            "Davao City",                 // City/Town
            "Davao Del Sur",              // Province
            "8080"});                     // ZIP
    CONTACTS_TABLE.emplace_back(ContactDetailsTableItem {
            "2054993",                    // Employee ID <!Same as employeeID>
            "",                           // Email
            "09123334567",                // Contact number 1
            ""});                         // Contact number 2
    PERSONAL_ID_TABLE.emplace_back(PersonalIdTableItem {
            "2054993",                    // Employee ID <!Same as employeeID>
            "Driver's License",           // Type
            "N04-10-0215655"});           // ID-number

    //------- 2073155
    EMPLOYEES_TABLE.emplace_back(EmployeeTableItem{
            "2073155",                    // Employee ID <!Make sure this is unique>
            "Manny",                      // First name
            "Pacman",                     // Middle name
            "Pacquiao",                   // Last name
            "1988/10/25",                 // B-date
            "M",                          // Gender
            "Delivery Personnel",         // Position
            "ACTIVE",                     // Status - ACTIVE, ON-LEAVE or INACTIVE
            false});                      // System user
    ADDRESS_TABLE.emplace_back(AddressTableItem {
            "2073155",                    // Employee ID <!Same as employeeID>
            "Palermo St., Mahayahay",     // Line 1
            "Opon",                       // Line 2
            "Lapu-Lapu City",             // City/Town
            "Cebu",                       // Province
            "6015"});                     // ZIP
    CONTACTS_TABLE.emplace_back(ContactDetailsTableItem {
            "2073155",                    // Employee ID <!Same as employeeID>
            "",                           // Email
            "09123334567",                // Contact number 1
            ""});                         // Contact number 2
    PERSONAL_ID_TABLE.emplace_back(PersonalIdTableItem {
            "2073155",                    // Employee ID <!Same as employeeID>
            "SSS",                        // Type
            "014-135-188-813"});          // ID-number
    //-------
}

void StackDB::populateProducts() {
    // If you want to add a product to our in-memory DB, put it here

    //------- Copy starting from the line below
    PRODUCT_TABLE.emplace_back(ProductTableItem {
            "1125478744",                 // Barcode <!Make sure this is unique>
            "JNJ-CHP-SML-RED",            // SKU
            "Chippy",                     // Name
            "Original flavor",            // Description
            "Grocery",                    // Category
            "Jack n Jill",                // Brand
            "pc",                         // Unit of measurement (check the UOM_TABLE)
            "10",                         // Stocks remaining
            "High",                       // Status
            "8.00",                       // Original Price
            "10.00",                      // Selling Price
            "Alturas Supermarket",        // Supplier name
            "AltSmkt6325"});              // Supplier code
    //------- End here

    PRODUCT_TABLE.emplace_back(ProductTableItem {
            "1254854545",                 // Barcode <!Make sure this is unique>
            "NNN-COL-NNN-NNN",            // SKU
            "Mantika",                    // Name
            "Cooking oil",                // Description
            "Grocery",                    // Category
            "No Brand",                   // Brand
            "cp",                         // Unit of measurement (check the UOM_TABLE)
            "100",                        // Stocks remaining
            "High",                       // Status
            "5.00",                       // Original Price
            "6.00",                       // Selling Price
            "Alturas Supermarket",        // Supplier name
            "AltSmkt6325"});              // Supplier code

    PRODUCT_TABLE.emplace_back(ProductTableItem {
            "5554833345",                 // Barcode <!Make sure this is unique>
            "NNN-SUG-NNN-NNN",            // SKU
            "Asukal Puti",                // Name
            "Sugar",                      // Description
            "Grocery",                    // Category
            "No Brand",                   // Brand
            "g",                          // Unit of measurement (check the UOM_TABLE)
            "100",                        // Stocks remaining
            "High",                       // Status
            "5.00",                       // Original Price
            "6.00",                       // Selling Price
            "Alturas Supermarket",        // Supplier name
            "AltSmkt6325"});              // Supplier code

    PRODUCT_TABLE.emplace_back(ProductTableItem {
            "5684833847",                 // Barcode <!Make sure this is unique>
            "UNI-BIO-NNN-NNN",            // SKU
            "Biogesic",                   // Name
            "Paracetamol",                // Description
            "Medicine",                   // Category
            "Unilab",                     // Brand
            "pc",                         // Unit of measurement (check the UOM_TABLE)
            "20",                         // Stocks remaining
            "High",                       // Status
            "5.00",                       // Original Price
            "6.00",                       // Selling Price
            "Sab Pharmacy",               // Supplier name
            "SABPHARM210"});              // Supplier code

    PRODUCT_TABLE.emplace_back(ProductTableItem {
            "4844811887",                 // Barcode <!Make sure this is unique>
            "COK-COK-LAR-NNN",            // SKU
            "Coke 1L",                    // Name
            "Coke 1L bottle",             // Description
            "Beverage",                   // Category
            "Coca Cola",                  // Brand
            "pc",                         // Unit of measurement (check the UOM_TABLE)
            "20",                         // Stocks remaining
            "High",                       // Status
            "5.00",                       // Original Price
            "6.00",                       // Selling Price
            "Pengavator",                 // Supplier name
            "PGVTOR"});                   // Supplier code
}

void StackDB::populateCustomers() {
    // If you want to add a customer to our in-memory DB, put it here

    //------- Copy starting from the line below
    CUSTOMER_TABLE.emplace_back(CustomerTableItem {
            "CMJD12AB56CD",               // Customer ID <!Make sure this is unique>
            "John",                       // First name
            "Trump",                      // Middle name
            "Doe",                        // Last name
            "1998/01/04",                 // B-date
            "M"});                        // Gender
    ADDRESS_TABLE.emplace_back(AddressTableItem {
            "CMJD12AB56CD",               // Customer ID <!Same as CustomerID above>
            "Back St., Boys Back",        // Line 1
            "Alright",                    // Line 2
            "Lapu-Lapu City",             // City/Town
            "Cebu",                       // Province
            "6015"});                     // ZIP
    CONTACTS_TABLE.emplace_back(ContactDetailsTableItem {
            "CMJD12AB56CD",               // Customer ID <!Same as CustomerID above>
            "",                           // Email
            "09123334567",                // Contact number 1
            ""});                         // Contact number 2
    PERSONAL_ID_TABLE.emplace_back(PersonalIdTableItem {
            "CMJD12AB56CD",               // Customer ID <!Same as CustomerID above>
            "SSS",                        // Type
            "014-135-188-813"});          // ID-number
    //------- End here

    CUSTOMER_TABLE.emplace_back(CustomerTableItem {
            "CMTP25XB56ZD",               // Customer ID <!Make sure this is unique>
            "Thinking",                   // First name
            "TP",                         // Middle name
            "Pinoy",                      // Last name
            "1995/04/09",                 // B-date
            "M"});                        // Gender
    ADDRESS_TABLE.emplace_back(AddressTableItem {
            "CMTP25XB56ZD",               // Customer ID <!Same as CustomerID above>
            "Highland St., Longliner",    // Line 1
            "",                           // Line 2
            "Some City",                  // City/Town
            "Davao",                      // Province
            "6000"});                     // ZIP
    CONTACTS_TABLE.emplace_back(ContactDetailsTableItem {
            "CMTP25XB56ZD",               // Customer ID <!Same as CustomerID above>
            "Tp_reach@gmail.com",         // Email
            "09181113245",                // Contact number 1
            ""});                         // Contact number 2
    PERSONAL_ID_TABLE.emplace_back(PersonalIdTableItem {
            "CMTP25XB56ZD",               // Customer ID <!Same as CustomerID above>
            "SSS",                        // Type
            "014-135-188-813"});          // ID-number

    CUSTOMER_TABLE.emplace_back(CustomerTableItem {
            "CMAR88TR15TC",               // Customer ID <!Make sure this is unique>
            "April",                      // First name
            "Boy",                        // Middle name
            "Regino",                     // Last name
            "1987/08/05",                 // B-date
            "M"});                        // Gender
    ADDRESS_TABLE.emplace_back(AddressTableItem {
            "CMAR88TR15TC",               // Customer ID <!Same as CustomerID above>
            "Tondo",                      // Line 1
            "",                           // Line 2
            "Metro Manila",               // City/Town
            "Manila",                     // Province
            "6000"});                     // ZIP
    CONTACTS_TABLE.emplace_back(ContactDetailsTableItem {
            "CMAR88TR15TC",               // Customer ID <!Same as CustomerID above>
            "",                           // Email
            "09181113245",                // Contact number 1
            ""});                         // Contact number 2
    PERSONAL_ID_TABLE.emplace_back(PersonalIdTableItem {
            "CMAR88TR15TC",               // Customer ID <!Same as CustomerID above>
            "SSS",                        // Type
            "014-135-188-813"});          // ID-number

    CUSTOMER_TABLE.emplace_back(CustomerTableItem {
            "CMAA95TZ45FR",               // Customer ID <!Make sure this is unique>
            "Alexa",                      // First name
            "Speech",                     // Middle name
            "Amazon",                     // Last name
            "2001/10/03",                 // B-date
            "F"});                        // Gender
    ADDRESS_TABLE.emplace_back(AddressTableItem {
            "CMAA95TZ45FR",               // Customer ID <!Same as CustomerID above>
            "SamSam St., Local Area",     // Line 1
            "",                           // Line 2
            "Mandaue City",               // City/Town
            "Cebu",                       // Province
            "6014"});                     // ZIP
    CONTACTS_TABLE.emplace_back(ContactDetailsTableItem {
            "CMAA95TZ45FR",               // Customer ID <!Same as CustomerID above>
            "",                           // Email
            "09181113245",                // Contact number 1
            ""});                         // Contact number 2
    PERSONAL_ID_TABLE.emplace_back(PersonalIdTableItem {
            "CMAA95TZ45FR",               // Customer ID <!Same as CustomerID above>
            "SSS",                        // Type
            "014-135-188-813"});          // ID-number

    CUSTOMER_TABLE.emplace_back(CustomerTableItem {
            "CMJB73YN64LB",               // Customer ID <!Make sure this is unique>
            "Jeff",                       // First name
            "Amazon",                     // Middle name
            "Bezos",                      // Last name
            "1975/01/12",                 // B-date
            "M"});                        // Gender
    ADDRESS_TABLE.emplace_back(AddressTableItem {
            "CMJB73YN64LB",               // Customer ID <!Same as CustomerID above>
            "Tabon, Purok 7",             // Line 1
            "San Francisco",              // Line 2
            "Dubai",                      // City/Town
            "Bohol",                      // Province
            "6314"});                     // ZIP
    CONTACTS_TABLE.emplace_back(ContactDetailsTableItem {
            "CMJB73YN64LB",               // Customer ID <!Same as CustomerID above>
            "",                           // Email
            "09181113245",                // Contact number 1
            ""});                         // Contact number 2
    PERSONAL_ID_TABLE.emplace_back(PersonalIdTableItem {
            "CMJB73YN64LB",               // Customer ID <!Same as CustomerID above>
            "SSS",                        // Type
            "014-135-188-813"});          // ID-number
}

void StackDB::populateUOM() {
    // If you want to add a unit of measurement to our in-memory DB, put it here

    //------- Copy starting from the line below
    UOM_TABLE.emplace_back(UOMTableItem {
            "1",                          // ID <!Make sure this is unique>
            "Liter",                      // Unit Name
            "L"});                        // Abbreviation
    //------- End here

    UOM_TABLE.emplace_back(UOMTableItem {
            "2",                          // ID <!Make sure this is unique>
            "Milliliter",                 // Unit Name
            "mL"});                       // Abbreviation
    UOM_TABLE.emplace_back(UOMTableItem {
            "3",                          // ID <!Make sure this is unique>
            "Kilogram",                   // Unit Name
            "kg"});                       // Abbreviation
    UOM_TABLE.emplace_back(UOMTableItem {
            "4",                          // ID <!Make sure this is unique>
            "Gram",                       // Unit Name
            "g"});                        // Abbreviation
    UOM_TABLE.emplace_back(UOMTableItem {
            "5",                          // ID <!Make sure this is unique>
            "Piece",                      // Unit Name
            "pc"});                       // Abbreviation
    UOM_TABLE.emplace_back(UOMTableItem {
            "6",                          // ID <!Make sure this is unique>
            "Cup",                        // Unit Name
            "cp"});                       // Abbreviation
}

void StackDB::populateSales() {
    // Empty for now
}

}  // namespace db
}  // namespace dataprovider