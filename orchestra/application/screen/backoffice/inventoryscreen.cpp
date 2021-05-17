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
#include "inventoryscreen.hpp"
#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <general.hpp>  // pscore utility
#include <generalhelper.hpp>  // view utility
#include <informationscreen.hpp>
#include <logger/loghelper.hpp>
#include <screencommon.hpp>

namespace screen {
namespace backoffice {

// Product fields
const std::vector<std::string> DOMAIN_FIELDS {
    "Product.SKU",
    "Product.Name",
    "Product.Description",
    "Product.Category",
    "Product.Brand",
    "Product.UOM",
    "Product.Stock",
    "Product.Status",
    "Product.Original.Price",
    "Product.Sell.Price",
    "Product.Supplier.Name",
    "Product.Supplier.Code"
};

InventoryScreen::InventoryScreen() : mTableHelper({"Product", "Category", "Stock", "Price"},
            { &entity::Product::name, &entity::Product::category, &entity::Product::stock,
              &entity::Product::sellPrice }), isShowingDetailsScreen(false) {
    mfieldHelper.addField({entity::FIELD_BCODE, "Barcode", &entity::Product::setBarcode});
    mfieldHelper.addField({entity::FIELD_SKU, "SKU", &entity::Product::setSKU});
    mfieldHelper.addField({entity::FIELD_PNAME, "Name", &entity::Product::setName});
    mfieldHelper.addField({entity::FIELD_PDESC, "Description", &entity::Product::setDescription});
    mfieldHelper.addField({entity::FIELD_CTGR, "Category", &entity::Product::setCategory});
    mfieldHelper.addField({entity::FIELD_BRAND, "Brand", &entity::Product::setBrand});
    mfieldHelper.addField({entity::FIELD_UOM, "UOM", &entity::Product::setUOM});
    mfieldHelper.addField({entity::FIELD_STOCK, "Stock", &entity::Product::setStock});
    mfieldHelper.addField({entity::FIELD_PSTATUS, "Status", &entity::Product::setStatus});
    mfieldHelper.addField({entity::FIELD_OPRICE, "Orig. Price",
                           &entity::Product::setOriginalPrice});
    mfieldHelper.addField({entity::FIELD_SPRICE, "Sell Price", &entity::Product::setSellPrice});
    mfieldHelper.addField({entity::FIELD_SPNAME, "Supplier", &entity::Product::setSupplierName});
    mfieldHelper.addField({entity::FIELD_SPCODE, "Supp. Code", &entity::Product::setSupplierCode});
}

void InventoryScreen::show(std::promise<defines::display>* promise) {
    mCoreController = domain::inventory::createInventoryModule(
                    std::make_shared<dataprovider::inventory::InventoryDataProvider>(),
                    std::make_shared<InventoryScreen>());
    // Get the products from Core then cache the list
    queryProductsList();
    // Landing
    showLandingScreen();
    /*!
     * Screen navigation
     * Stay in the current screen until action() returns false (i.e. switch screen is required)
    */
    do {} while (action(getUserSelection(), promise));
}

void InventoryScreen::showLandingScreen() const {
    LOG_DEBUG("Showing inventory management screen");
    SCREENCOMMON().showTopBanner("Inventory Control");
    showProducts();
    showOptions();
}

void InventoryScreen::queryProductsList() {
    mTableHelper.setData(mCoreController->list());
}

void InventoryScreen::showProducts() const {
    LOG_DEBUG("Showing products list");
    std::cout << std::endl;
    mTableHelper.printTable();
}

void InventoryScreen::showProductDetails(bool showIndex) const {
    LOG_DEBUG("Showing product details");
    const entity::Product& selectedProduct = mTableHelper.getSelectedData();
    SCREENCOMMON().showTopBanner("Product Information");
    screen::InformationScreen<entity::Product> infoScreen(selectedProduct);
    infoScreen.showItemIndex(showIndex);
    infoScreen.showBasicInformation();
    infoScreen.showOptions();
}

void InventoryScreen::removeProduct() {
    LOG_INFO("Deleting product");
    if (mCoreController->remove(mTableHelper.getSelectedData().barcode())
        == domain::inventory::INVENTORYAPISTATUS::SUCCESS) {
       // Remove the product from our table
       mTableHelper.deleteSelectedData();
    }
}

void InventoryScreen::createProduct() {
    LOG_DEBUG("Showing create product screen");
    SCREENCOMMON().showTopBanner("Create Product");
    std::cout << "Type [space] for an empty entry" << std::endl;
    std::vector<std::string> requiredFields;  // Used to request re-input of failed fields
    entity::Product newProduct;
    do {
        // Input product details
        mfieldHelper.getInputsFromField(&newProduct, requiredFields);
        if (mfieldHelper.isBreak()) {
            // User requested to cancel
            break;
        }
        // Reset after filling the fields
        requiredFields.clear();

        std::map<std::string, std::string> validationResult;
        if (mCoreController->save(newProduct, &validationResult)
            != domain::inventory::INVENTORYAPISTATUS::SUCCESS) {
            requiredFields = app::util::extractMapKeys(validationResult);
            SCREENCOMMON().printErrorList(app::util::extractMapValues(validationResult));
            checkAndPrintUOMError(requiredFields);
        } else {
            std::cout << "Product created successfully!" << std::endl;
        }
    } while (!requiredFields.empty());  // repeat input until new product is created
}

void InventoryScreen::updateProduct() {
    showProductDetails(true);  // true - request to show the index # of each data
    LOG_DEBUG("Showing product update options");
    const std::string field = SCREENCOMMON().getUpdateField(DOMAIN_FIELDS);
    if (field.empty()) {
        std::cout << "Invalid selection." << std::endl;
        return;
    }
    {   // Update operation
        std::vector<std::string> requiredFields = { field };
        std::map<std::string, std::string> validationResult;
        entity::Product product = mTableHelper.getSelectedData();
        do {
            mfieldHelper.getInputsFromField(&product, requiredFields);
            if (mfieldHelper.isBreak()) {
                // User requested to cancel
                break;
            }
            // Reset validation results
            validationResult.clear();
            if (mCoreController->save(product, &validationResult)
                != domain::inventory::INVENTORYAPISTATUS::SUCCESS) {
                requiredFields = app::util::extractMapKeys(validationResult);
                SCREENCOMMON().printErrorList(app::util::extractMapValues(validationResult));
                checkAndPrintUOMError(requiredFields);
            }
        } while (!validationResult.empty());  // repeat input until new employee is created
        mTableHelper.setData((mTableHelper.getCurrentIndex()), product);
    }
}

InventoryScreen::Options InventoryScreen::getUserSelection() {
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
    } else if (userInput == "d" && isShowingDetailsScreen) {
            return Options::OP_DELETE;
    } else if (userInput == "c" && !isShowingDetailsScreen) {
            return Options::OP_CREATE;
    } else if (userInput == "u" && isShowingDetailsScreen) {
            return Options::OP_UPDATE;
    }  // add more options here

    // Default invalid option
    return Options::INVALID;
}

bool InventoryScreen::action(Options option, std::promise<defines::display>* nextScreen) {
    bool switchScreenIsRequired = false;
    switch (option) {
        case Options::LANDING:
            // Warning: There are recurssions inside this switch-case()
            // These must be considered when doing changes for Options::LANDING
            queryProductsList();
            showLandingScreen();
            isShowingDetailsScreen = false;  // Must set to false
            break;
        case Options::INVALID:
            invalidOptionSelected();
            break;
        case Options::OP_READ:
            showProductDetails();
            isShowingDetailsScreen = true;  // Must set to true
            break;
        case Options::OP_DELETE:
            removeProduct();
            // Go back to landing screen after removing the product
            action(Options::LANDING, nextScreen);
            break;
        case Options::OP_CREATE:
            createProduct();
            // Go back to landing screen after creating the product
            action(Options::LANDING, nextScreen);
            break;
        case Options::OP_UPDATE:
            updateProduct();
            showProductDetails();  // refresh details screen
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

void InventoryScreen::checkAndPrintUOMError(const std::vector<std::string>& requiredFields) const {
    if (std::find(requiredFields.begin(), requiredFields.end(), entity::FIELD_UOM)
        != requiredFields.end()) {
        std::cout << "List of valid units:" << std::endl;
        for (const entity::UnitOfMeasurement& uom : mCoreController->getMeasurementList()) {
             std::cout << "- " << uom.abbreviation() << std::endl;
        }
        std::cout << std::endl;
    }
}

void InventoryScreen::showProductsEmptyPopup() {
    std::cout << "Products record is empty." << std::endl;
}

void InventoryScreen::showDataNotReadyScreen() {
    std::cout << "Data is not ready." << std::endl;
}

void InventoryScreen::showSuccessfullyRemoved(const std::string& barcode) {
    std::cout << "Successfully removed product with barcode " << barcode << std::endl;
}

}  // namespace backoffice
}  // namespace screen
