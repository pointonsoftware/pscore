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
#include "customermgmtcontroller.hpp"
#include <memory>
#include <logger/loghelper.hpp>
#include <validator/personvalidator.hpp>

namespace domain {
namespace customermgmt {

CustomerManagementController::CustomerManagementController(
            const CustomerMgmtDataPtr& data,
            const CustomerMgmtViewPtr& view) {
    if ((data == nullptr) || (view == nullptr)) {
        throw std::invalid_argument("Received a nulltpr argument");
    }
    mDataProvider = data;
    mView = view;
}

std::vector<entity::Customer> CustomerManagementController::list() {
    LOG_DEBUG("Getting the list of products");
    return mCachedList;
}

entity::Customer CustomerManagementController::get(const std::string& id) {
    LOG_DEBUG("Getting customer %s data", id.c_str());
    return entity::Customer{};
}

CUSTOMERMGMTAPISTATUS CustomerManagementController::save(const entity::Customer& customer,
                                                ValidationErrors* validationResult) {
    LOG_DEBUG("Saving customer information");
    if (!validationResult) {
        LOG_ERROR("Validation-message container is not initialized");
        return CUSTOMERMGMTAPISTATUS::UNINITIALIZED;
    }
    // Cleanup the container
    validationResult->clear();
    // Validate fields
    {
        LOG_DEBUG("Validating fields");
        entity::validator::PersonValidator validator(customer);
        validationResult->insert(validator.result().begin(), validator.result().end());
    }
    if (!validationResult->empty()) {
        LOG_WARN("Entity contains invalid data. Returning validation results.");
        dumpValidationResult(*(validationResult));
        return CUSTOMERMGMTAPISTATUS::FAILED;
    }
    return CUSTOMERMGMTAPISTATUS::SUCCESS;
}

void CustomerManagementController::create(const entity::Customer& customer) {
    LOG_DEBUG("Creating customer data", customer.ID().c_str());
}

void CustomerManagementController::update(const entity::Customer& customer) {
    LOG_DEBUG("Updating customer data", customer.ID().c_str());
}

void CustomerManagementController::dumpValidationResult(
                const ValidationErrors& validationErrors) const {
    LOG_DEBUG("Dumping validation result");
    for (auto const &result : validationErrors) {
        LOG_DEBUG(std::string(result.first + " -> " + result.second).c_str());
    }
}

CUSTOMERMGMTAPISTATUS CustomerManagementController::remove(const std::string& id) {
    LOG_DEBUG("Removing customer %s", id.c_str());
    return CUSTOMERMGMTAPISTATUS::SUCCESS;
}

CustomerMgmtControllerPtr createCustomerMgmtModule(
                    const CustomerMgmtDataPtr& data,
                    const CustomerMgmtViewPtr& view) {
    return std::make_unique<CustomerManagementController>(data, view);
}

}  // namespace customermgmt
}  // namespace domain
