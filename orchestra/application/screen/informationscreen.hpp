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
#include <iomanip>
#include <iostream>
#include <string>
#include "screendefines.hpp"
#include <entity/customer.hpp>
#include <entity/employee.hpp>
#include <entity/product.hpp>
#include <entity/user.hpp>
#include <screencommon.hpp>

namespace screen {

template <typename T>
class InformationScreen {
 public:
    explicit InformationScreen(const T& t) : mInfo(&t) {}
    InformationScreen() = delete;
    ~InformationScreen() = default;
    void showBasicInformation();
    void showContactDetails() {
        SCREENCOMMON().printColumns({"Contact Details"}, true);
        printItem("Phone", mInfo->contactDetails().phone1());
        printItem("Phone 2", mInfo->contactDetails().phone2());
        printItem("Email", mInfo->contactDetails().email());
    }

    void showAddress() {
        SCREENCOMMON().printColumns({"Address"}, true);
        printItem("Address 1", mInfo->address().line1());
        printItem("Address 2", mInfo->address().line2());
        printItem("City/Town", mInfo->address().cityTown());
        printItem("Province", mInfo->address().province());
        printItem("Zip Code", mInfo->address().zip());
    }

    void showPersonalIds() {
        SCREENCOMMON().printColumns({"Personal Identification"}, true);
        for (size_t count = 1; count <= mInfo->personalIds().size(); ++count) {
            const std::string details(mInfo->personalIds()[count-1].type()
                                      + " " + defines::DELIMETER_DASH + " "
                                      + mInfo->personalIds()[count-1].number());
            SCREENCOMMON().printItemText("ID " + std::to_string(count), details);
        }
    }

    void showOptions() const {
        std::cout << std::endl << std::endl;
        SCREENCOMMON().printColumns({"[u] - Update", "[d] - Delete", "[b] - Back"},
                                    true, false);
    }

    void showItemIndex(bool show) {
        mShowIndex = show;
    }

 private:
    const T* mInfo = nullptr;
    bool mShowIndex = false;
    unsigned int mIndex = 0;
    const size_t MAX_SPACE = 4;

    void printItem(const std::string& label, const std::string& value) {
        if (!mShowIndex) {
            // Display label and value as-is
            SCREENCOMMON().printItemText(label, value);
        } else {
            // Spacing
            const size_t space = MAX_SPACE - std::to_string(mIndex + 1).length();
            // Print index
            std::cout << "[" << std::to_string(++mIndex) << std::left << std::setw(space) << "] ";
            // Show dash if value is empty
            SCREENCOMMON().printItemText(label, value.empty() ? "-" : value);
        }
    }
};

}  // namespace screen

#endif  // ORCHESTRA_APPLICATION_SCREEN_INFORMATIONSCREEN_HPP_