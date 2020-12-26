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
#ifndef ORCHESTRA_APPLICATION_SCREEN_SCREENIFACE_HPP_
#define ORCHESTRA_APPLICATION_SCREEN_SCREENIFACE_HPP_
#include <algorithm>
#include <future>
#include <string>
#include <vector>
#include <screencommon.hpp>
#include <screendefines.hpp>

namespace screen {

class ScreenInterface {
 public:
    ScreenInterface() = default;
    virtual ~ScreenInterface() = default;

    virtual void show(std::promise<defines::display>* promise) = 0;

 protected:
    class FieldHelper {
     public:
        explicit FieldHelper(const std::vector<std::string>& requiredFields)
            : mRequiredFields(requiredFields) {}
        FieldHelper() = delete;
        // Find the field from the "requiredFields" vector
        inline bool requires(const std::string& field) const {
            if (mRequiredFields.empty()) {
                // Field is required by default
                 return true;
            }
            return std::find(mRequiredFields.begin(), mRequiredFields.end(), field)
                    != mRequiredFields.end();
        }
     private:
        const std::vector<std::string>& mRequiredFields;
    };

    // Simulate an input area or text box of GUI
    inline void inputArea(std::function<void(const std::string&)> func,
                          const std::string& label, bool fieldIsRequired) const {
        if (fieldIsRequired) {
            func(SCREENCOMMON().getInput(label));
        }
    }
};

}  // namespace screen

#endif  // ORCHESTRA_APPLICATION_SCREEN_SCREENIFACE_HPP_