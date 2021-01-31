/**************************************************************************************************
*                                            PSCORE                                               *
*                               Copyright (C) 2021 Pointon Software                               *
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
#ifndef ORCHESTRA_APPLICATION_UTILITY_INFORMATIONFIELDHELPER_HPP_
#define ORCHESTRA_APPLICATION_UTILITY_INFORMATIONFIELDHELPER_HPP_
#include <string>
#include <vector>
#include <entity/address.hpp>
#include <entity/contactdetails.hpp>
#include <entity/person.hpp>
#include <entity/personalid.hpp>
#include "fieldhelper.hpp"

namespace app {
namespace utility {

class InformationFieldHelper {
 public:
    InformationFieldHelper() {
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
                                &entity::ContactDetails::setEmail});
        // Personal ID
        mIDfieldHelper.addField({entity::FIELD_PNID_IDT, "ID Type",
                                &entity::PersonalId::setType});
        mIDfieldHelper.addField({entity::FIELD_PNID_IDN, "ID Number",
                                &entity::PersonalId::setNumber});
    }
    ~InformationFieldHelper() = default;

    // Get user inputs from the requested fields
    inline void getInputsFromField(entity::Person* entity,
                                   const std::vector<std::string>& reqField) {
        if (entity == nullptr) {
           throw std::invalid_argument("Received a nulltpr argument for getInputsFromField()");
        }
        // Find the field from the requested fields vector
        const auto& requested = [&reqField](const std::string& field) {
            if (reqField.empty()) {
                // All fields are requested by default
                return true;
            }
            return std::find(reqField.begin(), reqField.end(), field) != reqField.end();
        };
        mIsBreak = true;  // We break by default
        // Address
        entity::Address address = entity->address();
        mAddressfieldHelper.getInputsFromField(&address, reqField);
        if (mAddressfieldHelper.isBreak()) {
            // User requested to cancel
            return;
        }
        entity->setAddress(address);
        // Contact details
        entity::ContactDetails contactDetails = entity->contactDetails();
        mContactfieldHelper.getInputsFromField(&contactDetails, reqField);
        if (mContactfieldHelper.isBreak()) {
            // User requested to cancel
            return;
        }
        entity->setPhoneNumbers(contactDetails.phone1(), contactDetails.phone2());
        entity->setEmail(contactDetails.email());
        // Ask if user wants to input a valid/government ID
        if (requested("PersonalId.Type") || requested("PersonalId.Number")) {
            entity::PersonalId personalId;
            // We're creating a new entity, ask if the entity has a Valid ID
            bool idFieldsRequired = SCREENCOMMON().getYesNoInput("Has government ID (y/n)") == "y";
            if (idFieldsRequired) {
                mIDfieldHelper.getInputsFromField(&personalId, reqField);
                if (mIDfieldHelper.isBreak()) {
                    // User requested to cancel
                    return;
                }
                // Add a new one
                entity->addPersonalId(personalId.type(), personalId.number());
            }
        }
        mIsBreak = false;
    }

    // Returns true if the user requested to abort the input request
    bool isBreak() const {
        return mIsBreak;
    }

 private:
    FieldHelper<entity::Address> mAddressfieldHelper;
    FieldHelper<entity::ContactDetails> mContactfieldHelper;
    FieldHelper<entity::PersonalId> mIDfieldHelper;
    bool mIsBreak = false;
};

}  // namespace utility
}  // namespace app
#endif  // ORCHESTRA_APPLICATION_UTILITY_INFORMATIONFIELDHELPER_HPP_
