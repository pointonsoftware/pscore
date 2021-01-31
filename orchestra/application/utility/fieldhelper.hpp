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
#ifndef ORCHESTRA_APPLICATION_UTILITY_FIELDHELPER_HPP_
#define ORCHESTRA_APPLICATION_UTILITY_FIELDHELPER_HPP_
#include <algorithm>
#include <string>
#include <utility>
#include <vector>
#include "screencommon.hpp"

namespace app {
namespace utility {

template <typename EntityType>
class FieldHelper {
 public:
    FieldHelper() = default;
    ~FieldHelper() = default;

    struct Field {
        std::string fieldName;
        std::string label;
        std::function<void(EntityType*, const std::string&)> entiySetter;
    };

    // Add an input field
    inline void addField(Field&& field) {
        mEntityFields.emplace_back(std::forward<Field>(field));
    }

    // Get user inputs from the requested fields
    inline void getInputsFromField(EntityType* entity, const std::vector<std::string>& reqField) {
        // Find the field from the requested fields vector
        const auto& requested = [&reqField](const std::string& field) {
            if (reqField.empty()) {
                // All fields are requested by default
                return true;
            }
            return std::find(reqField.begin(), reqField.end(), field) != reqField.end();
        };
        mIsBreak = false;  // We must reset this flag before starting
        for (const Field& field : mEntityFields) {
            if (!requested(field.fieldName)) {
                continue;
            }
            std::string input = SCREENCOMMON().getInput(field.label);
            if (input == "x" || input == "b") {
                mIsBreak = true;
                break;
            }
            field.entiySetter(entity, input);
        }
    }

    // Returns true if the user requested to abort the input request
    bool isBreak() const {
        return mIsBreak;
    }

 private:
    std::vector<Field> mEntityFields;
    bool mIsBreak = false;
};

}  // namespace utility
}  // namespace app
#endif  // ORCHESTRA_APPLICATION_UTILITY_FIELDHELPER_HPP_
