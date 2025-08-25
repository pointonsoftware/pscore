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
#include <string>
#include <vector>
#include <logger/loghelper.hpp>
#include <validator/productvalidator.hpp>

namespace domain {
namespace inventory {

InventoryController::InventoryController(const InventoryDataPtr& data,
                                         const InventoryViewPtr& view)
                                         : BaseController(data, view) {
    mCachedList.setEntityKeyFn(&entity::Product::barcode);
}

std::vector<entity::Product> InventoryController::list() {
    LOG_DEBUG("Retrieving all products data");
    mCachedList.fill(mDataProvider->getProducts());
    if (!mCachedList.hasData()) {
        LOG_WARN("There are no products on record");
        mView->showProductsEmptyPopup();
        return {};
    }
    LOG_INFO("Successfully retrieved %d products.", mCachedList.dataCount());
    return mCachedList.get();
}

entity::Product InventoryController::getProduct(const std::string& barcode) {
    LOG_DEBUG("Getting product %s", barcode.c_str());
    const std::vector<entity::Product>::iterator& iter = mCachedList.find(barcode);
    if (iter != mCachedList.endOfData()) {
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
        entity::validator::ProductValidator validator(product,
            // Set valid UOM abbreviations
            [this]() {
                std::vector<std::string> uomAbbr;
                for (const entity::UnitOfMeasurement& uom : getMeasurementList()) {
                    uomAbbr.emplace_back(uom.abbreviation());
                }
                return uomAbbr;
            }(),
            getCategoryList());
        validationResult->merge(validator.result());
    }

    if (!(validationResult->empty())) {
        LOG_WARN("Entity contains invalid data. Returning validation results.");
        dumpValidationResult(*(validationResult));
        return INVENTORYAPISTATUS::FAILED;
    }
    // Decide if it's a create or update request
    if (mCachedList.isExists(product.barcode())) {
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
    mCachedList.insert(product);
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
    const std::vector<entity::Product>::iterator it = mCachedList.find(product.barcode());
    *it = product;
    LOG_INFO("Product %s information updated", product.name().c_str());
}

INVENTORYAPISTATUS InventoryController::remove(const std::string& barcode) {
    LOG_DEBUG("Removing product %s", barcode.c_str());
    const std::vector<entity::Product>::iterator it =
                     mCachedList.find(barcode);
    if (it == mCachedList.endOfData()) {
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

std::vector<entity::UnitOfMeasurement> InventoryController::getMeasurementList() {
    mCachedUOMs.fill(mDataProvider->getUOMs());
    return mCachedUOMs.get();
}

INVENTORYAPISTATUS InventoryController::save(const entity::UnitOfMeasurement& uom) {
    LOG_DEBUG("Adding new unit of measurement %s", uom.name().c_str());
    mCachedUOMs.setEntityKeyFn(&entity::UnitOfMeasurement::ID);
    if (mCachedUOMs.isExists(uom.ID())) {
        LOG_ERROR("Unit of measurement ID %s already exists", uom.ID().c_str());
        return INVENTORYAPISTATUS::FAILED;
    }
    mCachedUOMs.setEntityKeyFn(&entity::UnitOfMeasurement::name);
    if (mCachedUOMs.isExists(uom.name())) {
        LOG_ERROR("Unit of measurement %s already exists", uom.name().c_str());
        return INVENTORYAPISTATUS::FAILED;
    }
    mCachedUOMs.setEntityKeyFn(&entity::UnitOfMeasurement::abbreviation);
    if (mCachedUOMs.isExists(uom.abbreviation())) {
        LOG_ERROR("Unit of measurement abbreviation %s already exists", uom.abbreviation().c_str());
        return INVENTORYAPISTATUS::FAILED;
    }
    // Add to DB
    mDataProvider->createUOM(uom);
    // Add to cache
    mCachedUOMs.insert(uom);
    LOG_INFO("Successfully added uom %s", uom.name().c_str());
    return INVENTORYAPISTATUS::SUCCESS;
}

INVENTORYAPISTATUS InventoryController::removeUOM(const std::string& id) {
    LOG_DEBUG("Removing unit of measurement");
    mCachedUOMs.setEntityKeyFn(&entity::UnitOfMeasurement::ID);
    const std::vector<entity::UnitOfMeasurement>::iterator it = mCachedUOMs.find(id);
    if (it == mCachedUOMs.endOfData()) {
        LOG_ERROR("Unit of measurement ID %s was not found.", id.c_str());
        return INVENTORYAPISTATUS::NOT_FOUND;
    }
    LOG_INFO("Removing %s", it->name().c_str());
    // Remove from DB
    mDataProvider->removeUOM(id);
    // Remove from cache
    mCachedUOMs.erase(it);
    LOG_INFO("Successfully removed uom %s", id.c_str());
    return INVENTORYAPISTATUS::SUCCESS;
}

std::vector<std::string> InventoryController::getCategoryList() {
    return mDataProvider->getCategories();
}

INVENTORYAPISTATUS InventoryController::addCategory(const std::string& category) {
    const std::vector<std::string>& categories = mDataProvider->getCategories();
    if (std::find(categories.begin(), categories.end(), category) != categories.end()) {
        LOG_ERROR("Category %s already exists", category.c_str());
        return INVENTORYAPISTATUS::FAILED;
    }
    mDataProvider->createCategory(category);
    return INVENTORYAPISTATUS::SUCCESS;
}

INVENTORYAPISTATUS InventoryController::removeCategory(const std::string& category) {
    const std::vector<std::string>& categories = mDataProvider->getCategories();
    if (std::find(categories.begin(), categories.end(), category) == categories.end()) {
        LOG_ERROR("Category %s does not exist", category.c_str());
        return INVENTORYAPISTATUS::NOT_FOUND;
    }
    mDataProvider->removeCategory(category);
    return INVENTORYAPISTATUS::SUCCESS;
}

InventoryControllerPtr createInventoryModule(const InventoryDataPtr& data,
                                             const InventoryViewPtr& view) {
    return std::make_unique<InventoryController>(data, view);
}

}  // namespace inventory
}  // namespace domain
