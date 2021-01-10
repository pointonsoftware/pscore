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
#include <generator/chargenerator.hpp>
#include <logger/loghelper.hpp>
#include <validator/addressvalidator.hpp>
#include <validator/contactdetailsvalidator.hpp>
#include <validator/personalidvalidator.hpp>
#include <validator/personvalidator.hpp>

namespace domain {
namespace customermgmt {

CustomerManagementController::CustomerManagementController(const CustomerMgmtDataPtr& data,
                                                           const CustomerMgmtViewPtr& view) {
    if ((data == nullptr) || (view == nullptr)) {
        throw std::invalid_argument("Received a nulltpr argument");
    }
    mDataProvider = data;
    mView = view;
}

std::vector<entity::Customer> CustomerManagementController::list() {
    LOG_DEBUG("Getting the list of customers");
    mCachedList = mDataProvider->getCustomers();
    if (mCachedList.empty()) {
        LOG_WARN("There are no customers on record");
        mView->showListIsEmptyPopup();
        return {};
    }
    LOG_INFO("Successfully retrieved customers list. Size: %d", mCachedList.size());
    return mCachedList;
}

entity::Customer CustomerManagementController::get(const std::string& id) {
    LOG_DEBUG("Getting customer %s data", id.c_str());
    const std::vector<entity::Customer>::iterator& iter = find(id);
    if (iter != mCachedList.end()) {
        LOG_INFO("Found customer %s", id.c_str());
        return *iter;
    } else {
        LOG_ERROR("Requested customer was not found");
        return entity::Customer{};
    }
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
    // Validate customer
    {
        LOG_DEBUG("Validating fields");
        entity::validator::PersonValidator validator(customer);
        validationResult->merge(validator.result());
    }
    // validate address
    {
        entity::validator::AddressValidator validator(customer.address());
        validationResult->merge(validator.result());
    }
    // validate contact information
    {
        entity::validator::ContactDetailsValidator validator(customer.contactDetails());
        validationResult->merge(validator.result());
    }
    // validate ID
    {
        for (const entity::PersonalId& personalId : customer.personalIds()) {
            entity::validator::PersonalIDValidator validator(personalId);
            validationResult->merge(validator.result());
        }
    }
    if (!validationResult->empty()) {
        LOG_WARN("Entity contains invalid data. Returning validation results.");
        dumpValidationResult(*(validationResult));
        return CUSTOMERMGMTAPISTATUS::FAILED;
    }
    // Todo: decide if it's a create or update request
    create(customer);
    return CUSTOMERMGMTAPISTATUS::SUCCESS;
}

void CustomerManagementController::create(const entity::Customer& data) {
    // Gnerate ID and create a new customer
    entity::Customer newCustomer(
        // Todo (code) - need to ensure this ID is unique
        utility::chargenerator::generateCustomerID(data.firstName(), data.lastName()),
        data.firstName(), data.middleName(), data.lastName(), data.birthdate(),
        data.gender());
    newCustomer.setAddress(data.address());
    newCustomer.setPhoneNumbers(data.contactDetails().phone_number_1,
                                data.contactDetails().phone_number_2);
    for (const entity::PersonalId& id : data.personalIds()) {
        newCustomer.addPersonalId(id.type, id.id_number);
    }
    LOG_DEBUG("Creating customer data %s", newCustomer.ID().c_str());
    // Adding new customer
    mDataProvider->create(newCustomer);
    /*!
     * Todo (code) - add checking if create is successful from dataprovider
     * before updating the cache
    */
    mCachedList.emplace_back(newCustomer);
    LOG_INFO("Customer %s %s added", newCustomer.firstName().c_str(),
                                     newCustomer.lastName().c_str());
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

std::vector<entity::Customer>::iterator CustomerManagementController::find(const std::string& id) {
    return std::find_if(mCachedList.begin(), mCachedList.end(),
                [&id](const entity::Customer& e) { return e.ID() == id; });
}

CustomerMgmtControllerPtr createCustomerMgmtModule(
                    const CustomerMgmtDataPtr& data,
                    const CustomerMgmtViewPtr& view) {
    return std::make_unique<CustomerManagementController>(data, view);
}

}  // namespace customermgmt
}  // namespace domain
