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
#include "screencommon.hpp"
#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <screendefines.hpp>
#include <cfg/config.hpp>  // utility

constexpr char CORE_CONFIG[] = "psinfo.cfg";
constexpr char CORE_VERSION_MASK[] = "x.x.x";

namespace screen {

void ScreenCommon::clearScreen() const {
#ifdef __WIN32__
    std::system("cls");
#else
    std::system("clear");
#endif
}

void ScreenCommon::showTopBanner(const std::string& currentScreen) const {
    clearScreen();
    printHorizontalBorder(defines::BORDER_CHARACTER_1);
    printTitleText("");
    printTitleText(std::string("---- CORE "+ std::string(getCoreVersion()) +" ----"));
    printTitleText("");
    printTitleText("Console  Application");
    printTitleText("");
    printTitleText("Enter [x] if you want to exit");
    printHorizontalBorder(defines::BORDER_CHARACTER_1);
    printTitleText(currentScreen);
    printHorizontalBorder(defines::BORDER_CHARACTER_1);
}

void ScreenCommon::printTitleText(const std::string& text) const {
    const Indent indents = calculateIndents(VerticalAlignment::CENTER,
                                            defines::SCREEN_WIDTH, text);
    std::cout << defines::BORDER_CHARACTER_1
              << indents.start << text << indents.end
              << defines::BORDER_CHARACTER_1 << std::endl;
}

void ScreenCommon::printItemText(const std::string& label, const std::string& item) const {
    if (item.empty()) {
        // Don't show anything if item is empty
        return;
    }
    std::cout << std::left << std::setw(defines::LABEL_WIDTH)
              << label  << defines::LABEL_BOUNDARY << " "
              << item   << std::endl;
}

void ScreenCommon::printColumns(const std::vector<std::string>& columns,
                                bool isHeader, bool showColumnBorders) const {
    const unsigned int columnWidth = defines::SCREEN_WIDTH / columns.size();
    unsigned int modulo = defines::SCREEN_WIDTH % columns.size();
    if (isHeader) {
        // Print upper border
        printHorizontalBorder(defines::BORDER_CHARACTER_2);
    }
    for (unsigned int i = 0; i < columns.size(); i++) {
        const Indent indents = calculateIndents(isHeader ?
                                                VerticalAlignment::CENTER :
                                                VerticalAlignment::LEFT,
                                                columnWidth,
                                                columns[i]);
        /*!
         * If showColumnBorders is true, print defines::BORDER_CHARACTER_3
         * Else, we just print defines::BORDER_CHARACTER_3 on the first column
        */
        std::cout << (showColumnBorders ? defines::BORDER_CHARACTER_3 :
                     (i == 0 ? defines::BORDER_CHARACTER_3 :  ' '))
                  << indents.start << columns[i] << indents.end
                  // If columns.size() is odd, do +1 space for each column width
                  << [&modulo]() { return modulo > 0 ? (modulo--, " ") : ""; }();
    }
    // End column border
    std::cout << defines::BORDER_CHARACTER_3 << std::endl;
    if (isHeader) {
        // Print bottom border
        printHorizontalBorder(defines::BORDER_CHARACTER_2);
    }
}

void ScreenCommon::printHorizontalBorder(char borderCharacter) const {
    std::string borderString;
    for (unsigned int i = 0; i <= defines::SCREEN_WIDTH; ++i) {
        borderString += borderCharacter;
    }
    std::cout << borderString << std::endl;
}

void ScreenCommon::printErrorList(const std::vector<std::string>& errors) const {
    std::cout << "Invalid inputs:" << std::endl;
    for (const std::string& error : errors) {
         std::cout << "- " << error << std::endl;
    }
    // Let the user confirm after viewing the validation results
    std::cout << "Press [Enter] to update fields..." << std::endl;
    std::cin.ignore();
    std::cin.get();
}

std::string ScreenCommon::getInput(const std::string& label, unsigned int maxSize) const {
    std::string userInput;
    do {
        std::cout << std::left << std::setw(defines::LABEL_WIDTH)
                  << label << defines::LABEL_BOUNDARY << " ";
        if (std::iswspace(std::cin.peek())) {
            // Ignore if cin is not empty
            std::cin.ignore();
        }
        std::getline(std::cin, userInput);
        if ((maxSize == 0) || (userInput.size() <= maxSize)) {
            if (!userInput.empty() &&
                std::all_of(userInput.begin(), userInput.end(), ::isspace)) {
                // Clear if input only contains whitespaces
                userInput.clear();
            }
            break;
        }
        std::cout << "Error: Input is too long." << std::endl;
        userInput.clear();
    } while (1);
    return userInput;
}

std::string ScreenCommon::getYesNoInput(const std::string& label) const {
    std::string userInput;
    do {
        userInput.clear();
        std::cout << std::left << std::setw(defines::LABEL_WIDTH)
                  << label  << defines::LABEL_BOUNDARY << " ";
        std::cin >> userInput;
        std::transform(userInput.begin(), userInput.end(), userInput.begin(),
                       [](unsigned char c){ return std::tolower(c); });
    } while (userInput != "y" && userInput != "n");
    return userInput;
}

void ScreenCommon::inputArea(std::function<void(const std::string&)> func,
                             const std::string& label, bool fieldIsRequired) const {
    if (fieldIsRequired) {
        func(SCREENCOMMON().getInput(label));
    }
}

ScreenCommon::Indent ScreenCommon::calculateIndents(VerticalAlignment vAlign,
                                                    unsigned int width,
                                                    const std::string& text) const {
    Indent indents;
    switch (vAlign) {
        case VerticalAlignment::LEFT:
            indents.start = " ";  // Left offset
            indents.end = std::string((width - text.size() - 2), ' ');
            break;
        case VerticalAlignment::CENTER:
            indents.start = std::string((width - text.size()) / 2, ' ');
            indents.end = indents.start;
            if (!(text.size() % 2)) {
                indents.end = indents.start.substr(0, indents.start.size() - 1);
            }
            break;
        case VerticalAlignment::RIGHT:
            break;
        default:
            break;
    }

    return indents;
}

const std::string ScreenCommon::getCoreVersion() const {
    static std::string version = CORE_VERSION_MASK;
    if (version == CORE_VERSION_MASK) {
        utility::Config config(CORE_CONFIG);
        version = config.get("version", CORE_VERSION_MASK);
    }
    return version;
}

}  // namespace screen