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
#ifndef ORCHESTRA_APPLICATION_SCREEN_INFORMATIONSCREEN_HPP_
#define ORCHESTRA_APPLICATION_SCREEN_INFORMATIONSCREEN_HPP_
#include <iostream>
#include <string>
#include "screencommon.hpp"

namespace screen {

template <typename T>
class InformationScreen {
 public:
    explicit InformationScreen(const T& t) : mInfo(&t) {}
    ~InformationScreen() = default;

    const InformationScreen& showBasicInformation() {
        std::cout << std::endl << "Basic Info" << std::endl << std::endl;
        SCREENCOMMON().printItemText("First Name", mInfo->firstName());
        SCREENCOMMON().printItemText("Middle Name", mInfo->middleName());
        SCREENCOMMON().printItemText("Last Name", mInfo->lastName());
        SCREENCOMMON().printItemText("Birthdate", mInfo->birthdate());
        SCREENCOMMON().printItemText("Gender", mInfo->gender());
        return *this;
    }

    const InformationScreen& showContactDetails() const {
        std::cout << std::endl << std::endl  << "Contact Details" << std::endl << std::endl;
        for (size_t count = 1; count <= mInfo->contactDetails().phone_number.size(); ++count) {
            SCREENCOMMON().printItemText("Phone " + std::to_string(count),
                                        mInfo->contactDetails().phone_number[count-1]);
        }
        std::cout << "Email       : " << mInfo->contactDetails().email << std::endl;
        return *this;
    }

    const InformationScreen& showUserAddress() const {
        std::cout << std::endl << std::endl  << "Address" << std::endl << std::endl;
        SCREENCOMMON().printItemText("House No.", mInfo->address().housenumber);
        SCREENCOMMON().printItemText("Lot", mInfo->address().lot);
        SCREENCOMMON().printItemText("Block", mInfo->address().block);
        SCREENCOMMON().printItemText("Street", mInfo->address().street);
        SCREENCOMMON().printItemText("Subdivision", mInfo->address().subdivision);
        SCREENCOMMON().printItemText("Sitio", mInfo->address().sitio);
        SCREENCOMMON().printItemText("Purok", mInfo->address().purok);
        SCREENCOMMON().printItemText("Barangay", mInfo->address().barangay);
        SCREENCOMMON().printItemText("City/Town", mInfo->address().city_town);
        SCREENCOMMON().printItemText("Province", mInfo->address().province);
        SCREENCOMMON().printItemText("Zip Code", mInfo->address().zip);
        return *this;
    }

    const InformationScreen& showUserPersonalIds() const {
        std::cout << std::endl << std::endl  << "Personal Identification" << std::endl << std::endl;
        for (size_t count = 1; count <= mInfo->personalIds().size(); ++count) {
            const std::string details(mInfo->personalIds()[count-1].type
                                + defines::DELIMETER_DASH
                                + mInfo->personalIds()[count-1].id_number);
            SCREENCOMMON().printItemText("ID " + std::to_string(count), details);
        }
        return *this;
    }

 private:
    const T* mInfo;
};

}  // namespace screen

#endif  // ORCHESTRA_APPLICATION_SCREEN_INFORMATIONSCREEN_HPP_