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
std::vector<StackDB::AddressTableItem> StackDB::ADDRESS_TABLE;
std::vector<StackDB::ContactDetailsTableItem> StackDB::CONTACTS_TABLE;
std::vector<StackDB::PersonalIdTableItem> StackDB::PERSONAL_ID_TABLE;

StackDB::StackDB() {
    populateEmployees();
}

void StackDB::populateEmployees() {
    // If you want to add a user/employee to our in-memory DB, put it here

    //------- Copy starting from the line below
    EMPLOYEES_TABLE.emplace_back(EmployeeTableItem {
            "2014566",                    // Employee ID <!Make sure this is unique>
            "BenZiv",                     // First name
            "Hero",                       // Middle name
            "Garcia",                     // Last name
            "10/15/2020",                 // B-date
            "Male",                       // Gender
            "Admin",                      // Position
            "2020"});                     // PIN <!Unique> <!Empty if non-user>
    ADDRESS_TABLE.emplace_back(AddressTableItem {
            "2014566",                    // Employee ID <!Must be the same as above>
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
            "2014566",                    // Employee ID <!Must be the same as above>
            "test@gmail.com",             // Email
            "09123334567",                // Contact number 1
            "09987654321"});              // Contact number 2
    PERSONAL_ID_TABLE.emplace_back(PersonalIdTableItem {
            "2014566",                    // Employee ID <!Must be the same as above>
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
            "Male",                       // Gender
            "Manager",                    // Position
            "2021"});                     // PIN <!Unique> <!Empty if non-user>
    ADDRESS_TABLE.emplace_back(AddressTableItem {
            "2019542",                    // Employee ID <!Must be the same as above>
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
            "2019542",                    // Employee ID <!Must be the same as above>
            "zznn@gmail.com",             // Email
            "09123334567",                // Contact number 1
            ""});                         // Contact number 2
    PERSONAL_ID_TABLE.emplace_back(PersonalIdTableItem {
            "2019542",                    // Employee ID <!Must be the same as above>
            "Driver's License",           // Type
            "N04-10-021355"});            // ID-number

    //------- 2098472
    EMPLOYEES_TABLE.emplace_back(EmployeeTableItem {
            "2098472",                    // Employee ID <!Make sure this is unique>
            "Juana",                      // First name
            "Santos",                     // Middle name
            "Dela Cruz",                  // Last name
            "10/18/2020",                 // B-date
            "Female",                     // Gender
            "Cashier",                    // Position
            "2022"});                     // PIN <!Unique> <!Empty if non-user>
    ADDRESS_TABLE.emplace_back(AddressTableItem {
            "2098472",                    // Employee ID <!Must be the same as above>
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
            "2098472",                    // Employee ID <!Must be the same as above>
            "juana@gmail.com",            // Email
            "09123334567",                // Contact number 1
            ""});                         // Contact number 2
    PERSONAL_ID_TABLE.emplace_back(PersonalIdTableItem {
            "2098472",                    // Employee ID <!Must be the same as above>
            "Driver's License",           // Type
            "N04-10-0215655"});           // ID-number

    //------- 2054993
    EMPLOYEES_TABLE.emplace_back(EmployeeTableItem {
            "2054993",                    // Employee ID <!Make sure this is unique>
            "Rodrigo",                    // First name
            "Roa",                        // Middle name
            "Duterte",                    // Last name
            "10/17/1977",                 // B-date
            "Male",                       // Gender
            "Security Guard",             // Position
            ""});                         // PIN <!Unique> <!Empty if non-user>
    ADDRESS_TABLE.emplace_back(AddressTableItem {
            "2054993",                    // Employee ID <!Must be the same as above>
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
            "2054993",                    // Employee ID <!Must be the same as above>
            "",                           // Email
            "09123334567",                // Contact number 1
            ""});                         // Contact number 2
    PERSONAL_ID_TABLE.emplace_back(PersonalIdTableItem {
            "2054993",                    // Employee ID <!Must be the same as above>
            "Driver's License",           // Type
            "N04-10-0215655"});           // ID-number

    //------- 2073155
    EMPLOYEES_TABLE.emplace_back(EmployeeTableItem{
            "2073155",                    // Employee ID <!Make sure this is unique>
            "Chris",                      // First name
            "White",                      // Middle name
            "Brown",                      // Last name
            "10/25/1988",                 // B-date
            "Male",                       // Gender
            "Delivery Personel",          // Position
            ""});                         // PIN <!Unique> <!Empty if non-user>
    ADDRESS_TABLE.emplace_back(AddressTableItem {
            "2073155",                    // Employee ID <!Must be the same as above>
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
            "2073155",                    // Employee ID <!Must be the same as above>
            "",                           // Email
            "09123334567",                // Contact number 1
            ""});                         // Contact number 2
    PERSONAL_ID_TABLE.emplace_back(PersonalIdTableItem {
            "2073155",                    // Employee ID <!Must be the same as above>
            "SSS",                        // Type
            "014-135-188-813"});          // ID-number
    //-------
}

}  // namespace db
}  // namespace dataprovider