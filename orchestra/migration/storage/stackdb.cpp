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

std::vector<entity::Employee> StackDB::employeesList;
std::vector<entity::User> StackDB::usersList;

StackDB::StackDB() {
    populateUsers();
    populateEmployees();
}

void StackDB::populateUsers() {
    // If you want to add a user to our in-memory DB, put it here

    //------- Copy starting from the line below
    usersList.emplace_back(
            dynamic_cast<entity::User&>(
             entity::User("BenZiv",                     // First name
                          "H",                          // Middle name
                          "Garcia",                     // Last name
                          "10/15/2020",                 // B-date
                          "Male",                       // Gender
                          "10001",                      // Employee ID <!Make sure this is unique>
                          "Admin",                      // Position
                          "2020")                       // PIN <!Make sure this is unique>
                          .addPhoneNumber("09123334567")
                          .addPersonalId("SSS", "003-311-150-413")
                          .addPersonalId("UMID", "04-1511167-8")
                          .setEmail("test@gmail.com")
                          .setAddress(
                                  {"",                  // housenumber
                                   "5",                 // lot
                                   "10",                // block
                                   "Petonia St.",       // Street
                                   "Camella Homes",     // Subdivision
                                   "",                  // Sitio
                                   "",                  // Purok
                                   "Basak",             // Barangay
                                   "Lapu-Lapu City",    // City/Town
                                   "Cebu",              // Province
                                   "6015"               // ZIP
    })));
    //------- End here

    usersList.emplace_back(
            dynamic_cast<entity::User&>(
             entity::User("Zandro",                     // First name
                          "Midldle",                    // Middle name
                          "Garcia",                     // Last name
                          "10/10/2020",                 // B-date
                          "Male",                       // Gender
                          "10002",                      // Employee ID <!Make sure this is unique>
                          "Manager",                    // Position
                          "2021")                       // PIN <!Make sure this is unique>
                          .addPhoneNumber("09123334567")
                          .addPersonalId("Driver's License", "N04-10-021355")
                          .setEmail("test2@gmail.com")
                          .setAddress(
                                  {"",                  // housenumber
                                   "",                  // lot
                                   "",                  // block
                                   "",                  // Street
                                   "",                  // Subdivision
                                   "Bacbacan",          // Sitio
                                   "",                  // Purok
                                   "San Francisco",     // Barangay
                                   "Malayong Dapit",    // City/Town
                                   "Davao",             // Province
                                   "6060"               // ZIP
    })));

    usersList.emplace_back(
            dynamic_cast<entity::User&>(
             entity::User("Juana",                      // First name
                          "Santos",                     // Middle name
                          "Dela Cruz",                  // Last name
                          "10/18/2020",                 // B-date
                          "Female",                     // Gender
                          "10003",                      // Employee ID <!Make sure this is unique>
                          "Cashier",                    // Position
                          "2022")                       // PIN <!Make sure this is unique>
                          .addPhoneNumber("09123334567")
                          .addPersonalId("Driver's License", "N04-10-021355")
                          .setEmail("Juana@gmail.com")
                          .setAddress(
                                  {"",                  // housenumber
                                   "2",                 // lot
                                   "6",                 // block
                                   "",                  // Street
                                   "BF Homes",          // Subdivision
                                   "",                  // Sitio
                                   "",                  // Purok
                                   "Agus",              // Barangay
                                   "Lapu-Lapu City",    // City/Town
                                   "Cebu",              // Province
                                   "6015"               // ZIP
    })));

    // Always append users to employees list (as users are also employees)
    employeesList.insert(std::end(employeesList), std::begin(usersList), std::end(usersList));
}

void StackDB::populateEmployees() {
    // Add employee here
    employeesList.emplace_back(
            dynamic_cast<entity::Employee&>(
             entity::Employee("Rodrigo",                // First name
                          "Roa",                        // Middle name
                          "Duterte",                    // Last name
                          "10/17/1977",                 // B-date
                          "Male",                       // Gender
                          "10004",                      // Employee ID <!Make sure this is unique>
                          "Security Guard")             // Position
                          .addPhoneNumber("09123334567")
                          .addPersonalId("Driver's License", "N04-10-021355")
                          .setEmail("duterte@gmail.com")
                          .setAddress(
                                  {"22",                // housenumber
                                   "1",                 // lot
                                   "21",                // block
                                   "",                  // Street
                                   "St. Andrews Hill",  // Subdivision
                                   "",                  // Sitio
                                   "",                  // Purok
                                   "Poblacion",         // Barangay
                                   "Davao City",        // City/Town
                                   "Davao",             // Province
                                   "6060"               // ZIP
    })));

    employeesList.emplace_back(
            dynamic_cast<entity::Employee&>(
             entity::Employee("Chris",                  // First name
                          "White",                      // Middle name
                          "Brown",                      // Last name
                          "10/18/1977",                 // B-date
                          "Male",                       // Gender
                          "10005",                      // Employee ID <!Make sure this is unique>
                          "Delivery Personel")          // Position
                          .addPhoneNumber("09123334567")
                          .addPersonalId("SSS", "014-135-188-813")
                          .setEmail("Chris_123@gmail.com")
                          .setAddress(
                                  {"18",                // housenumber
                                   "",                  // lot
                                   "",                  // block
                                   "Palermo St.",       // Street
                                   "",                  // Subdivision
                                   "Mahayahay",         // Sitio
                                   "",                  // Purok
                                   "Opon",              // Barangay
                                   "Lapu-Lapu City",    // City/Town
                                   "Cebu",              // Province
                                   "6015"               // ZIP
    })));
}

}  // namespace db
}  // namespace dataprovider