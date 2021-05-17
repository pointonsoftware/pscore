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
#ifndef ORCHESTRA_APPLICATION_UTILITY_SCREENCOMMON_HPP_
#define ORCHESTRA_APPLICATION_UTILITY_SCREENCOMMON_HPP_
#include <functional>
#include <string>
#include <vector>

#define SCREENCOMMON() screen::ScreenCommon::getInstance()

namespace screen {

class ScreenCommon {
 public:
    ~ScreenCommon() = default;
    static ScreenCommon& getInstance() {
        static ScreenCommon instance;
        return instance;
    }

    void clearScreen() const;

    // Outputs
    void showTopBanner(const std::string& currentScreen) const;
    void printTitleText(const std::string& text, bool showBorders = true) const;
    void printItemText(const std::string& label, const std::string& item) const;
    void printColumns(const std::vector<std::string>& columns,
                      bool isHeader = false, bool showColumnBorders = true) const;
    void printHorizontalBorder(char borderCharacter) const;
    void printErrorList(const std::vector<std::string>& errors) const;

    // Inputs
    std::string getInput(const std::string& label, unsigned int maxSize = 0) const;
    std::string getYesNoInput(const std::string& label) const;
    void inputArea(std::function<void(const std::string&)> func,
                   const std::string& label) const;
    const std::string getUpdateField(const std::vector<std::string>& fields) const;
    const std::string getCoreVersion() const;

 private:
    struct Indent {
        std::string start;
        std::string end;
    };

    enum class VerticalAlignment {
        LEFT,
        CENTER,
        RIGHT
    };

    ScreenCommon() = default;
    Indent calculateIndents(VerticalAlignment vAlign,
                            unsigned int width,
                            const std::string& text) const;
};

}  // namespace screen

#endif  // ORCHESTRA_APPLICATION_UTILITY_SCREENCOMMON_HPP_