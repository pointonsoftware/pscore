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
#ifndef CORE_ENTITY_VALIDATOR_VALIDATOR_HPP_
#define CORE_ENTITY_VALIDATOR_VALIDATOR_HPP_
#include <functional>
#include <vector>

namespace entity {
namespace validator {

enum ValidationResult {
    S_OK             = 0,
    S_INVALID_STRING = 1,
    S_EMPTY          = 2,
    S_TOO_LONG       = 3
};

class Validator {
 public:
    Validator() = default;
    virtual ~Validator() = default;

    inline ValidationResult result() {
        return mResult;
    }

 protected:
    std::vector<std::function<void()>> validationFunctions;
    ValidationResult mResult;

    inline void validate() {
        for (const auto& func : validationFunctions) {
            func();  // Run validator
            if (mResult != ValidationResult::S_OK) {
                // Break if result is not OK
                break;
            }
        }
    }
};

}  // namespace validator
}  // namespace entity
#endif  // CORE_ENTITY_VALIDATOR_VALIDATOR_HPP_