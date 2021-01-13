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
    mCachedList.fill(mDataProvider->getCustomers());
    if (!mCachedList.hasData()) {
        LOG_WARN("There are no customers on record");
        mView->showListIsEmptyPopup();
        return {};
    }
    LOG_INFO("Successfully retrieved customers list. Size: %d", mCachedList.dataCount());
    return mCachedList.get();
}

entity::Customer CustomerManagementController::get(const std::string& id) {
    LOG_DEBUG("Getting customer %s data", id.c_str());
    const std::vector<entity::Customer>::iterator& iter =
                     mCachedList.find(id, &entity::Customer::ID);
    if (iter == mCachedList.endOfData()) {
        LOG_ERROR("Requested customer was not found");
        return entity::Customer{};
    }
    LOG_INFO("Found customer %s", id.c_str());
    return *iter;
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
    // Decide if it's a create or update request
    if (mCachedList.isExists(customer.ID(), &entity::Customer::ID)) {
        update(customer);
    } else {
        create(customer);
    }
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
    mCachedList.insert(newCustomer);
    LOG_INFO("Customer %s %s added", newCustomer.firstName().c_str(),
                                     newCustomer.lastName().c_str());
}

void CustomerManagementController::update(const entity::Customer& customer) {
    LOG_DEBUG("Updating customer data", customer.ID().c_str());
    // Update actual data
    mDataProvider->update(customer);
    // Update cache list
    const std::vector<entity::Customer>::iterator it =
                    mCachedList.find(customer.ID(), &entity::Customer::ID);
    *it = customer;
    LOG_INFO("Customer %s information updated", customer.ID().c_str());
}

CUSTOMERMGMTAPISTATUS CustomerManagementController::remove(const std::string& id) {
    LOG_DEBUG("Removing customer %s", id.c_str());
    const std::vector<entity::Customer>::iterator it = mCachedList.find(id, &entity::Customer::ID);
    if (it == mCachedList.endOfData()) {
        LOG_ERROR("Customer with ID %s was not found in the cache list", id.c_str());
        mView->showDataNotReadyScreen();
        return CUSTOMERMGMTAPISTATUS::NOT_FOUND;
    }
    mDataProvider->remove(id);
    /*!
     * Todo (code) - check if mDataProvider successfully removed the customer
     * E.g. failure: mDataprovider lost db connection
    */
    // Remove from cache
    mCachedList.erase(it);
    mView->showSuccessfullyRemoved(id);
    return CUSTOMERMGMTAPISTATUS::SUCCESS;
}

CustomerMgmtControllerPtr createCustomerMgmtModule(
                    const CustomerMgmtDataPtr& data,
                    const CustomerMgmtViewPtr& view) {
    return std::make_unique<CustomerManagementController>(data, view);
}

}  // namespace customermgmt
}  // namespace domain
