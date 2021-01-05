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
#include <general.hpp>  // pscore utility
// view
#include <fieldhelper.hpp>
#include <generalhelper.hpp>
#include <informationscreen.hpp>
#include <screencommon.hpp>

namespace screen {
namespace backoffice {

// Product fields
const std::vector<std::string> InventoryScreen::productDomainFields {
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
              &entity::Product::sellPrice }), isShowingDetailsScreen(false) {}

void InventoryScreen::show(std::promise<defines::display>* promise) {
    mInventoryController = domain::inventory::createInventoryModule(
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
    SCREENCOMMON().showTopBanner("Inventory Control");
    showProducts();
    showOptions();
}

void InventoryScreen::queryProductsList() {
    mTableHelper.setData(mInventoryController->list());
}

void InventoryScreen::showProducts() const {
    std::cout << std::endl;
    mTableHelper.printTable();
    SCREENCOMMON().printHorizontalBorder(defines::BORDER_CHARACTER_2);
}

void InventoryScreen::showOptions() const {
    std::cout << std::endl << std::endl;
    SCREENCOMMON().printColumns({"[b] - Back", "[c] - Create", "[0] - Logout"}, true, false);
    std::cout << std::endl;
}

void InventoryScreen::showProductDetails(bool showIndex) const {
    const entity::Product& selectedProduct = mTableHelper.getSelectedData();
    SCREENCOMMON().showTopBanner("Product Information");
    screen::InformationScreen<entity::Product> infoScreen(selectedProduct);
    infoScreen.showItemIndex(showIndex);
    infoScreen.showBasicInformation();
    infoScreen.showOptions();
}

void InventoryScreen::removeProduct() {
    if (mInventoryController->remove(mTableHelper.getSelectedData().barcode())
        == domain::inventory::INVENTORYAPISTATUS::SUCCESS) {
       // Remove the product from our table
       mTableHelper.deleteSelectedData();
    }
}

void InventoryScreen::fillProductInformation(entity::Product* product,
                                             const std::vector<std::string>& requiredFields) const {
    app::utility::FieldHelper fieldHelper(requiredFields);
    SCREENCOMMON().inputArea(std::bind(&entity::Product::setBarcode, product,
        std::placeholders::_1), "Barcode", fieldHelper.requires(entity::FIELD_BCODE));
    SCREENCOMMON().inputArea(std::bind(&entity::Product::setSKU, product,
        std::placeholders::_1), "SKU", fieldHelper.requires(entity::FIELD_SKU));
    SCREENCOMMON().inputArea(std::bind(&entity::Product::setName, product,
        std::placeholders::_1), "Name", fieldHelper.requires(entity::FIELD_PNAME));
    SCREENCOMMON().inputArea(std::bind(&entity::Product::setDescription, product,
        std::placeholders::_1), "Description", fieldHelper.requires(entity::FIELD_PDESC));
    SCREENCOMMON().inputArea(std::bind(&entity::Product::setCategory, product,
        std::placeholders::_1), "Category", fieldHelper.requires(entity::FIELD_CTGR));
    SCREENCOMMON().inputArea(std::bind(&entity::Product::setBrand, product,
        std::placeholders::_1), "Brand", fieldHelper.requires(entity::FIELD_BRAND));
    SCREENCOMMON().inputArea(std::bind(&entity::Product::setUOM, product,
        std::placeholders::_1), "UOM", fieldHelper.requires(entity::FIELD_UOM));
    SCREENCOMMON().inputArea(std::bind(&entity::Product::setStock, product,
        std::placeholders::_1), "Stock", fieldHelper.requires(entity::FIELD_STOCK));
    SCREENCOMMON().inputArea(std::bind(&entity::Product::setStatus, product,
        std::placeholders::_1), "Status", fieldHelper.requires(entity::FIELD_PSTATUS));
    SCREENCOMMON().inputArea(std::bind(&entity::Product::setOriginalPrice, product,
        std::placeholders::_1), "Orig. Price", fieldHelper.requires(entity::FIELD_OPRICE));
    SCREENCOMMON().inputArea(std::bind(&entity::Product::setSellPrice, product,
        std::placeholders::_1), "Sell Price", fieldHelper.requires(entity::FIELD_SPRICE));
    SCREENCOMMON().inputArea(std::bind(&entity::Product::setSupplierName, product,
        std::placeholders::_1), "Supplier", fieldHelper.requires(entity::FIELD_SPNAME));
    SCREENCOMMON().inputArea(std::bind(&entity::Product::setSupplierCode, product,
        std::placeholders::_1), "Supp. Code", fieldHelper.requires(entity::FIELD_SPCODE));
}

void InventoryScreen::createProduct() {
    SCREENCOMMON().showTopBanner("Create Product");
    std::cout << "Type [space] for an empty entry" << std::endl;
    std::vector<std::string> requiredFields;  // Used to request re-input of failed fields
    entity::Product newProduct;
    do {
        // Input product details
        fillProductInformation(&newProduct, requiredFields);
        // Reset after filling the fields
        requiredFields.clear();

        std::map<std::string, std::string> validationResult;
        if (mInventoryController->save(newProduct, &validationResult)
            != domain::inventory::INVENTORYAPISTATUS::SUCCESS) {
            requiredFields = app::util::extractMapKeys(validationResult);
            SCREENCOMMON().printErrorList(app::util::extractMapValues(validationResult));
        } else {
            std::cout << "Product created successfully!" << std::endl;
        }
    } while (!requiredFields.empty());  // repeat input until new product is created
}

void InventoryScreen::updateProduct() {
    showProductDetails(true);  // true - request to show the index # of each data
    const std::string field = SCREENCOMMON().getUpdateField(productDomainFields);
    if (field.empty()) {
        std::cout << "Invalid selection." << std::endl;
        return;
    }
    {   // Update operation
        std::vector<std::string> requiredFields = { field };
        std::map<std::string, std::string> validationResult;
        entity::Product product = mTableHelper.getSelectedData();
        do {
            fillProductInformation(&product, requiredFields);
            // Reset validation results
            validationResult.clear();
            if (mInventoryController->save(product, &validationResult)
                != domain::inventory::INVENTORYAPISTATUS::SUCCESS) {
                requiredFields = app::util::extractMapKeys(validationResult);
                SCREENCOMMON().printErrorList(app::util::extractMapValues(validationResult));
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
            return Options::PRODUCT_DETAILS;
        }
    } else if (userInput == "d" && isShowingDetailsScreen) {
            return Options::PRODUCT_REMOVE;
    } else if (userInput == "c" && !isShowingDetailsScreen) {
            return Options::PRODUCT_CREATE;
    } else if (userInput == "u" && isShowingDetailsScreen) {
            return Options::PRODUCT_UPDATE;
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
        case Options::PRODUCT_DETAILS:
            showProductDetails();
            isShowingDetailsScreen = true;  // Must set to true
            break;
        case Options::PRODUCT_REMOVE:
            removeProduct();
            // Go back to landing screen after removing the product
            action(Options::LANDING, nextScreen);
            break;
        case Options::PRODUCT_CREATE:
            createProduct();
            // Go back to landing screen after creating the product
            action(Options::LANDING, nextScreen);
            break;
        case Options::PRODUCT_UPDATE:
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

void InventoryScreen::invalidOptionSelected() const {
    std::cout << "Sorry, that option is not yet available." << std::endl;
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
