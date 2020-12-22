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

namespace domain {
namespace inventory {

InventoryController::InventoryController(const std::shared_ptr<InventoryDataInterface>& data,
                                         const std::shared_ptr<InventoryViewInterface>& view) {
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

std::unique_ptr<InventoryControlInterface> createInventoryModule(
                    const std::shared_ptr<InventoryDataInterface>& data,
                    const std::shared_ptr<InventoryViewInterface>& view) {
    return std::make_unique<InventoryController>(data, view);
}

}  // namespace inventory
}  // namespace domain
