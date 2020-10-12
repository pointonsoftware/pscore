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

std::vector<entity::User> StackDB::usersList;

StackDB::StackDB() {
    populateUsers();
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
}
}  // namespace db
}  // namespace dataprovider