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
#ifndef CORE_VALIDATOR_VALIDATOR_HPP_
#define CORE_VALIDATOR_VALIDATOR_HPP_
#include <functional>
#include <string>
#include <unordered_map>
#include <utility>
#include <vector>

namespace entity {
namespace validator {

enum ValidationStatus {
    S_OK             = 0,
    S_INVALID_STRING = 1,
    S_EMPTY          = 2,
    S_INVALID_SIZE   = 3
};

// map [field that failed, error message to display]
typedef std::unordered_map<std::string, std::string> Errors;

class Validator {
 public:
    Validator() = default;
    virtual ~Validator() = default;

    inline Errors result() {
        return errors;
    }

 protected:
    std::vector<std::function<ValidationStatus()>> validationFunctions;

    inline void validate() {
        for (const auto& func : validationFunctions) {
            func();  // Run validator
        }
    }

    inline void addError(const std::string& field, const std::string& message) {
        errors.insert(std::make_pair(field, message));
    }

 private:
    // Populate this with errors
    Errors errors;
};

}  // namespace validator
}  // namespace entity
#endif  // CORE_VALIDATOR_VALIDATOR_HPP_