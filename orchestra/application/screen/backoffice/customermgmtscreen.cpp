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
const std::vector<std::string> DOMAIN_FIELDS {
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
              isShowingDetailsScreen(false) {
    // Basic info
    mCustomerfieldHelper.addField({entity::FIELD_FNAME, "First Name",
                            &entity::Employee::setFirstName});
    mCustomerfieldHelper.addField({entity::FIELD_MNAME, "Middle Name",
                            &entity::Employee::setMiddleName});
    mCustomerfieldHelper.addField({entity::FIELD_LNAME, "Last Name",
                            &entity::Employee::setLastName});
    mCustomerfieldHelper.addField({entity::FIELD_BDATE, "Birthdate (yyyy/mm/dd)",
                            &entity::Employee::setBirthdate});
    mCustomerfieldHelper.addField({entity::FIELD_GENDER, "Gender (M/F)",
                            &entity::Employee::setGender});
    // Address
    mAddressfieldHelper.addField({entity::FIELD_ADDR_LN1, "Address 1",
                            &entity::Address::setLine1});
    mAddressfieldHelper.addField({entity::FIELD_ADDR_LN2, "Address 2",
                            &entity::Address::setLine2});
    mAddressfieldHelper.addField({entity::FIELD_ADDR_CTY, "City/Town",
                            &entity::Address::setCityTown});
    mAddressfieldHelper.addField({entity::FIELD_ADDR_PRV, "Province",
                            &entity::Address::setProvince});
    mAddressfieldHelper.addField({entity::FIELD_ADDR_ZIP, "Zip",
                            &entity::Address::setZip});
    // Contact details
    mContactfieldHelper.addField({entity::FIELD_CONT_PH1, "Phone Number 1",
                            &entity::ContactDetails::setPhone1});
    mContactfieldHelper.addField({entity::FIELD_CONT_PH2, "Phone Number 2",
                            &entity::ContactDetails::setPhone2});
    mContactfieldHelper.addField({entity::FIELD_CONT_EML, "Email Address",
                            &entity::ContactDetails::setPhone2});
    // Personal ID
    mIDfieldHelper.addField({entity::FIELD_PNID_IDT, "ID Type",
                            &entity::PersonalId::setType});
    mIDfieldHelper.addField({entity::FIELD_PNID_IDN, "ID Number",
                            &entity::PersonalId::setNumber});
}

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

bool CustomerMgmtScreen::fillCustomerInformation(entity::Customer* customer,
                         const std::vector<std::string>& requiredFields) {
    const auto& requires = [&requiredFields](const std::string& field) {
        if (requiredFields.empty()) {
            // All fields are requested by default
            return true;
        }
        return std::find(requiredFields.begin(), requiredFields.end(), field)
                         != requiredFields.end();
    };

    // Ask if user wants to input a valid/government ID
    if (requires("PersonalId.Type") || requires("PersonalId.Number")) {
        entity::PersonalId personalId;
        // We're creating a new customer, ask if the customer has a Valid ID
        bool idFieldsRequired = SCREENCOMMON().getYesNoInput("Has government ID (y/n)") == "y";

        if (idFieldsRequired) {
            mIDfieldHelper.getInputsFromField(&personalId, requiredFields);
            if (mIDfieldHelper.isBreak()) {
                // User requested to cancel
            }
            // Add a new one
            customer->addPersonalId(personalId.type(), personalId.number());
        }
    }
    return true;
}

void CustomerMgmtScreen::createCustomer() {
    SCREENCOMMON().showTopBanner("Create Customer");
    std::cout << "Type [space] for an empty entry" << std::endl;
    std::vector<std::string> requiredFields;  // Used to request re-input of failed fields
    entity::Customer newCustomer;
    do {
        // Input customer details
        mCustomerfieldHelper.getInputsFromField(&newCustomer, requiredFields);
        if (mCustomerfieldHelper.isBreak()) {
            // User requested to cancel
            break;
        }

        entity::Address address = newCustomer.address();
        mAddressfieldHelper.getInputsFromField(&address, requiredFields);
        if (mAddressfieldHelper.isBreak()) {
            // User requested to cancel
            break;
        }
        newCustomer.setAddress(address);

        entity::ContactDetails contactDetails = newCustomer.contactDetails();
        mContactfieldHelper.getInputsFromField(&contactDetails, requiredFields);
        if (mContactfieldHelper.isBreak()) {
            // User requested to cancel
            break;
        }
        newCustomer.setPhoneNumbers(contactDetails.phone1(), contactDetails.phone2());
        newCustomer.setEmail(contactDetails.email());

        fillCustomerInformation(&newCustomer, requiredFields);
        // Reset after filling the fields
        requiredFields.clear();

        std::map<std::string, std::string> validationResult;
        if (mCoreController->save(newCustomer, &validationResult)
            != domain::customermgmt::CUSTOMERMGMTAPISTATUS::SUCCESS) {
            requiredFields = app::util::extractMapKeys(validationResult);
            SCREENCOMMON().printErrorList(app::util::extractMapValues(validationResult));
        } else {
            std::cout << "Customer created successfully!" << std::endl;
        }
    } while (!requiredFields.empty());  // repeat input until new customer is created
}

void CustomerMgmtScreen::updateCustomer() {
    showCustomerDetails(true);  // true - request to show the index # of each data
    // Get the field to update
    const std::string field = SCREENCOMMON().getUpdateField(DOMAIN_FIELDS);
    if (field.empty()) {
        std::cout << "Invalid selection." << std::endl;
        return;
    }
    /**
     *  We currently don't support updating the Personal ID field due to code complexity
     *  Track - https://github.com/pointonsoftware/pscore/issues/106
     */
    if ((field == "PersonalId.Type") || (field == "PersonalId.Number")) {
        std::cout << "Invalid selection." << std::endl;
        return;
    }
    {
        // Update operation
        std::vector<std::string> requiredFields = { field };
        std::map<std::string, std::string> validationResult;
        entity::Customer customerData = mTableHelper.getSelectedData();
        do {
            mCustomerfieldHelper.getInputsFromField(&customerData, requiredFields);
            if (mCustomerfieldHelper.isBreak()) {
                // User requested to cancel
                break;
            }
            fillCustomerInformation(&customerData, requiredFields);
            // Reset validation results
            validationResult.clear();
            if (mCoreController->save(customerData, &validationResult) !=
                domain::customermgmt::CUSTOMERMGMTAPISTATUS::SUCCESS) {
                requiredFields = app::util::extractMapKeys(validationResult);
                SCREENCOMMON().printErrorList(app::util::extractMapValues(validationResult));
            }
        } while (!validationResult.empty());  // repeat input until data is updated
        mTableHelper.setData((mTableHelper.getCurrentIndex()), customerData);
    }
}

void CustomerMgmtScreen::removeCustomer() {
    if (mCoreController->remove(mTableHelper.getSelectedData().ID())
          == domain::customermgmt::CUSTOMERMGMTAPISTATUS::SUCCESS) {
       // Remove the customer form
       mTableHelper.deleteSelectedData();
    }
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
            return Options::OP_READ;
        }
    } else if (userInput == "c" && !isShowingDetailsScreen) {
        return Options::OP_CREATE;
    } else if (userInput == "u" && isShowingDetailsScreen) {
        return Options::OP_UPDATE;
    } else if (userInput == "d" && isShowingDetailsScreen) {
        return Options::OP_DELETE;
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
        case Options::OP_READ:
            showCustomerDetails();
            isShowingDetailsScreen = true;  // Must set to true
            break;
        case Options::OP_CREATE:
            createCustomer();
            // Go back to landing screen after creating the customer
            action(Options::LANDING, nextScreen);
            break;
        case Options::OP_UPDATE:
            updateCustomer();
            showCustomerDetails();  // refresh employee details screen
            break;
        case Options::OP_DELETE:
            removeCustomer();
            action(Options::LANDING, nextScreen);
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
