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

std::vector<StackDB::EmployeeTableItem> StackDB::EMPLOYEES_TABLE;
std::vector<StackDB::UserTableItem> StackDB::USERS_TABLE;
std::vector<StackDB::AddressTableItem> StackDB::ADDRESS_TABLE;
std::vector<StackDB::ContactDetailsTableItem> StackDB::CONTACTS_TABLE;
std::vector<StackDB::PersonalIdTableItem> StackDB::PERSONAL_ID_TABLE;

StackDB::StackDB() {
    populateEmployees();
    // Admin user
    USERS_TABLE.emplace_back(UserTableItem {
            "2020202",                    // Unique User ID
            "Admin",                      // Role
            "1251",                       // PIN <!Unique> <!Empty if non-user>
            ""});                         // No employee ID
}

void StackDB::populateEmployees() {
    // If you want to add a user/employee to our in-memory DB, put it here

    //------- Copy starting from the line below
    EMPLOYEES_TABLE.emplace_back(EmployeeTableItem {
            "2014566",                    // Employee ID <!Make sure this is unique>
            "BenZiv",                     // First name
            "Hero",                       // Middle name
            "Garcia",                     // Last name
            "15/10/2020",                 // B-date
            "M",                          // Gender
            "Manager"});                  // Position
    USERS_TABLE.emplace_back(UserTableItem {
            "BGAR123",                    // User ID <!Make sure this is unique>
            "Manager",                    // Role
            "2020",                       // PIN
            "2014566"});                  // Link to employee ID
    ADDRESS_TABLE.emplace_back(AddressTableItem {
            "2014566",                    // Employee ID <!Same as employeeID>
            "",                           // housenumber
            "5",                          // lot
            "10",                         // block
            "Petunia St.",                // Street
            "Camella Homes",              // Subdivision
            "",                           // Sitio
            "",                           // Purok
            "Basak",                      // Barangay
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
            "10/10/2020",                 // B-date
            "M",                          // Gender
            "Cashier"});                  // Position
    USERS_TABLE.emplace_back(UserTableItem {
            "BGAR567",                    // User ID <!Make sure this is unique>
            "Cashier",                    // Role
            "2021",                       // PIN
            "2019542"});                  // Link to employee ID
    ADDRESS_TABLE.emplace_back(AddressTableItem {
            "2019542",                    // Employee ID <!Same as employeeID>
            "",                           // housenumber
            "",                           // lot
            "",                           // block
            "",                           // Street
            "",                           // Subdivision
            "Bacbacan",                   // Sitio
            "",                           // Purok
            "San Francisco",              // Barangay
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
            "18/10/2020",                 // B-date
            "F",                          // Gender
            "Cashier"});                  // Position
    USERS_TABLE.emplace_back(UserTableItem {
            "JDEL554",                    // User ID <!Make sure this is unique>
            "Cashier",                    // Role
            "2022",                       // PIN
            "2098472"});                  // Link to employee ID
    ADDRESS_TABLE.emplace_back(AddressTableItem {
            "2098472",                    // Employee ID <!Same as employeeID>
            "2",                          // housenumber
            "6",                          // lot
            "",                           // block
            "",                           // Street
            "BF Homes",                   // Subdivision
            "Bacbacan",                   // Sitio
            "",                           // Purok
            "Agus",                       // Barangay
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
            "17/10/1977",                 // B-date
            "M",                          // Gender
            "Security Guard"});           // Position
    ADDRESS_TABLE.emplace_back(AddressTableItem {
            "2054993",                    // Employee ID <!Same as employeeID>
            "22",                         // housenumber
            "1",                          // lot
            "16",                         // block
            "",                           // Street
            "St. Andrews Hills",          // Subdivision
            "",                           // Sitio
            "",                           // Purok
            "Poblacion",                  // Barangay
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
            "25/10/1988",                 // B-date
            "M",                          // Gender
            "Delivery Personnel"});       // Position
    ADDRESS_TABLE.emplace_back(AddressTableItem {
            "2073155",                    // Employee ID <!Same as employeeID>
            "18",                         // housenumber
            "",                           // lot
            "",                           // block
            "Palermo St.",                // Street
            "",                           // Subdivision
            "Mahayahay",                  // Sitio
            "",                           // Purok
            "Opon",                       // Barangay
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

}  // namespace db
}  // namespace dataprovider