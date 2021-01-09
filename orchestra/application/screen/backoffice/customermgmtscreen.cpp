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

// Customer fields
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
    // Get the customers from Core then cache the list
    queryCustomersList();
    // Landing
    showLandingScreen();
    /*!
     * Screen navigation
     * Stay in the current screen until action() returns false (i.e. switch screen is required)
    */
    do {} while (action(getUserSelection(), promise));
}

void CustomerMgmtScreen::showLandingScreen() const {
    SCREENCOMMON().showTopBanner("Customer Management");
    showCustomers();
    showOptions();
}

void CustomerMgmtScreen::queryCustomersList() {
    mTableHelper.setData(mCoreController->list());
}

void CustomerMgmtScreen::showCustomers() const {
    std::cout << std::endl;
    mTableHelper.printTable();
    SCREENCOMMON().printHorizontalBorder(defines::BORDER_CHARACTER_2);
}

void CustomerMgmtScreen::showCustomerDetails(bool showIndex) const {
    const entity::Customer& selectedCustomer = mTableHelper.getSelectedData();
    SCREENCOMMON().showTopBanner("Customer Information");
    screen::InformationScreen<entity::Customer> infoScreen(selectedCustomer);
    infoScreen.showItemIndex(showIndex);
    infoScreen.showBasicInformation();
    infoScreen.showAddress();
    infoScreen.showContactDetails();
    infoScreen.showPersonalIds();
    infoScreen.showOptions();
}

void CustomerMgmtScreen::showOptions() const {
    std::cout << std::endl << std::endl;
    SCREENCOMMON().printColumns({"[b] - Back", "[0] - Logout"}, true, false);
    std::cout << std::endl;
}

CustomerMgmtScreen::Options CustomerMgmtScreen::getUserSelection() {
    std::string userInput;
    std::cout << std::endl << "Select [option] > "; std::cin >> userInput;

    if (userInput == "x") {
        return Options::APP_EXIT;
    } else if (userInput == "b") {
         // We should return whatever was the previous screen
        // For now, we will check if the info screen is shown
        return isShowingDetailsScreen ? Options::LANDING : Options::DASHBOARD;
    } else if (userInput == "0") {
        return Options::LOGOUT;
    } else if (utility::isNumber(userInput) && !isShowingDetailsScreen) {
        // Check if input is within the valid indexes
        uint8_t input = std::stoi(userInput) - 1;
        if (input < mTableHelper.getDataCount()) {
            // Store user input as the selected index (zero based)
            mTableHelper.setCurrentIndex(input);
            return Options::CUSTOMER_DETAILS;
        }
    }  // add more options here

    // Default invalid option
    return Options::INVALID;
}

bool CustomerMgmtScreen::action(Options option, std::promise<defines::display>* nextScreen) {
    bool switchScreenIsRequired = false;
    switch (option) {
        case Options::LANDING:
            // Warning: There are recurssions inside this switch-case()
            // These must be considered when doing changes for Options::LANDING
            queryCustomersList();
            showLandingScreen();
            isShowingDetailsScreen = false;  // Must set to false
            break;
        case Options::INVALID:
            invalidOptionSelected();
            break;
        case Options::CUSTOMER_DETAILS:
            showCustomerDetails();
            isShowingDetailsScreen = true;  // Must set to true
            break;
        case Options::DASHBOARD:
            switchScreenIsRequired = true;
            nextScreen->set_value(defines::display::DASHBOARD);
            break;
        case Options::LOGOUT:
            switchScreenIsRequired = true;
            nextScreen->set_value(defines::display::LOGIN);
            break;
        case Options::APP_EXIT:  // Fall-through
        default:
            switchScreenIsRequired = true;
            nextScreen->set_value(defines::display::EXIT);
            break;
    }
    // Return "false" if switch screen is required so we proceed to the next screen
    return !switchScreenIsRequired;
}

void CustomerMgmtScreen::invalidOptionSelected() const {
    std::cout << "Sorry, that option is not yet available." << std::endl;
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
