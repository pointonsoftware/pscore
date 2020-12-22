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
#ifndef CORE_VALIDATOR_PRODUCTVALIDATOR_HPP_
#define CORE_VALIDATOR_PRODUCTVALIDATOR_HPP_
#include <string>
// Parent
#include "validator.hpp"
// Entity
#include <entity/product.hpp>

namespace entity {
namespace validator {

/*!
 * Validation Rules:
 * All product fields are required (i.e. cannot be empty), except for the product description
 * Stocks must be a positive integer
 * Prices must be a valid number up to two decimal places (for cents)
*/

class ProductValidator : public Validator {
 public:
    explicit ProductValidator(const Product& product);
    ~ProductValidator() = default;

 private:
    const Product mProduct;
    // Validation functions
    ValidationStatus validateBarcode();
    ValidationStatus validateSKU();
    ValidationStatus validateName();
    ValidationStatus validateDescription();
    ValidationStatus validateCategory();
    ValidationStatus validateBrand();
    ValidationStatus validateUOM();
    ValidationStatus validateStock();
    ValidationStatus validateStatus();
    ValidationStatus validateOriginalPrice();
    ValidationStatus validateSellingPrice();
    ValidationStatus validateSupplierName();
    ValidationStatus validateSupplierCode();

    ValidationStatus checkEmptyString(const std::string& str,
                                      const std::string& field,
                                      const std::string& fieldString);
};

}  // namespace validator
}  // namespace entity
#endif  // CORE_VALIDATOR_PRODUCTVALIDATOR_HPP_