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
#include "inventorycontroller.hpp"
#include <algorithm>
#include <memory>
#include <logger/loghelper.hpp>
#include <validator/productvalidator.hpp>

namespace domain {
namespace inventory {

InventoryController::InventoryController(const InventoryDataPtr& data,
                                         const InventoryViewPtr& view) {
    if ((data == nullptr) || (view == nullptr)) {
        throw std::invalid_argument("Received a nulltpr argument");
    }
    mDataProvider = data;
    mView = view;
}

std::vector<entity::Product> InventoryController::list() {
    LOG_DEBUG("Getting the list of products");
    mCachedList = mDataProvider->getProducts();
    if (mCachedList.empty()) {
        LOG_WARN("There are no products on record");
        mView->showProductsEmptyPopup();
        return {};
    }
    LOG_INFO("Successfully retrieved products list. Size: %d", mCachedList.size());
    return mCachedList;
}

entity::Product InventoryController::getProduct(const std::string& barcode) {
    LOG_DEBUG("Getting product %s", barcode.c_str());
    const std::vector<entity::Product>::iterator& iter = find(barcode);
    if (iter != mCachedList.end()) {
        LOG_INFO("Found product %s", barcode.c_str());
        return *iter;
    } else {
        LOG_ERROR("Product was not found");
        return entity::Product{};
    }
}

INVENTORYAPISTATUS InventoryController::save(const entity::Product& product,
                                             ValidationErrors* validationResult) {
    LOG_DEBUG("Saving product information");
    if (!validationResult) {
        LOG_ERROR("Validation-message container is not initialized");
        return INVENTORYAPISTATUS::UNINITIALIZED;
    }
    // Cleanup the container
    validationResult->clear();
    // Validate fields
    {
        LOG_DEBUG("Validating fields");
        entity::validator::ProductValidator validator(product);
        validationResult->merge(validator.result());
    }
    if (!validationResult->empty()) {
        LOG_WARN("Entity contains invalid data. Returning validation results.");
        dumpValidationResult(*(validationResult));
        return INVENTORYAPISTATUS::FAILED;
    }
    // Decide if it's a create or update request
    if (isExists(product.barcode())) {
        update(product);
    } else {
        create(product);
    }
    return INVENTORYAPISTATUS::SUCCESS;
}

void InventoryController::create(const entity::Product& product) {
    LOG_DEBUG("Creating product with code %s", product.barcode().c_str());
    // Adding new product
    mDataProvider->create(product);
    /*!
     * Todo (code) - add checking if create is successful from dataprovider
     * before updating the cache
    */
    mCachedList.emplace_back(product);
    LOG_INFO("%s created with code %s", product.name().c_str(), product.barcode().c_str());
}

void InventoryController::update(const entity::Product& product) {
    LOG_DEBUG("Updating product with code %s", product.barcode().c_str());
    // Updating product
    mDataProvider->update(product);
    /*!
     * Todo (code) - add checking if update is successful from dataprovider
     * before updating the cache
    */
    // Update cache list
    const std::vector<entity::Product>::iterator it = find(product.barcode());
    *it = product;
    mCachedList.emplace_back(product);
    LOG_INFO("Product %s information updated", product.name().c_str());
}

INVENTORYAPISTATUS InventoryController::remove(const std::string& barcode) {
    LOG_DEBUG("Removing product %s", barcode.c_str());
    const std::vector<entity::Product>::iterator it = find(barcode);
    if (it == mCachedList.end()) {
        LOG_ERROR("Product %s was not found in the cache list", barcode.c_str());
        mView->showDataNotReadyScreen();
        return INVENTORYAPISTATUS::NOT_FOUND;
    }
    mDataProvider->removeWithBarcode(barcode);
    /*!
     * Todo (code) - check if mDataProvider successfully removed the product
     * E.g. failure: mDataprovider lost db connection
    */
    // Remove from cache
    mCachedList.erase(it);
    mView->showSuccessfullyRemoved(barcode);
    LOG_INFO("Successfully removed product %s", barcode.c_str());
    return INVENTORYAPISTATUS::SUCCESS;
}

bool InventoryController::isExists(const std::string& barcode) {
    return find(barcode) != mCachedList.end();
}

std::vector<entity::Product>::iterator InventoryController::find(const std::string& barcode) {
    return std::find_if(mCachedList.begin(), mCachedList.end(),
                [&barcode](const entity::Product& e) {
                    return e.barcode() == barcode;
                });
}

InventoryControllerPtr createInventoryModule(const InventoryDataPtr& data,
                                             const InventoryViewPtr& view) {
    return std::make_unique<InventoryController>(data, view);
}

}  // namespace inventory
}  // namespace domain
