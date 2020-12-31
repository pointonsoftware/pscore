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
#include "customermgmtscreen.hpp"
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <general.hpp>  // pscore utility
// view
#include <fieldhelper.hpp>
#include <generalhelper.hpp>
#include <informationscreen.hpp>
#include <screencommon.hpp>

namespace screen {
namespace backoffice {

// Product fields
const std::vector<std::string> CustomerMgmtScreen::domainFields {
        "Person.First.Name",
        "Person.Middle.Name",
        "Person.Last.Name",
        "Person.Birthdate",
        "Person.Gender",
        "Address.Line1",
        "Address.Line2",
        "Address.CityTown",
        "Address.Province",
        "Address.Zip",
        "ContactDetails.Phone1",
        "ContactDetails.Phone2",
        "ContactDetails.Email",
        "PersonalId.Type",
        "PersonalId.Number"
};

CustomerMgmtScreen::CustomerMgmtScreen() : mTableHelper({"ID", "First Name", "Last Name"},
            { &entity::Customer::ID, &entity::Customer::firstName, &entity::Customer::lastName }),
              isShowingDetailsScreen(false) {}

void CustomerMgmtScreen::show(std::promise<defines::display>* promise) {
    mCoreController = domain::customermgmt::createCustomerMgmtModule(
                    std::make_shared<dataprovider::customermgmt::CustomerDataProvider>(),
                    std::make_shared<CustomerMgmtScreen>());
    promise->set_value(defines::display::DASHBOARD);
}

void CustomerMgmtScreen::showListIsEmptyPopup() {
    std::cout << "Customer record is empty." << std::endl;
}

void CustomerMgmtScreen::showDataNotReadyScreen() {
    std::cout << "Data is not ready." << std::endl;
}

void CustomerMgmtScreen::showSuccessfullyRemoved(const std::string& customerName) {
    std::cout << "Successfully removed customer " << customerName << std::endl;
}

}  // namespace backoffice
}  // namespace screen
