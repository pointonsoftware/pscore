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
#include <cwctype>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <cfg/config.hpp>  // pscore utility
#include <generalutils.hpp>  // pscore utility
#include <screendefines.hpp>
#include "ui/theme.hpp"
#ifdef _WIN32
#include <windows.h>
#endif

constexpr char CORE_VERSION[] = "version";
constexpr char CORE_VERSION_MASK[] = "x.x.x";

namespace screen {

ScreenCommon::ScreenCommon() {
    // Initialize Windows console to support ANSI + UTF-8 if possible
#ifdef _WIN32
    // Enable ANSI escape sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        DWORD mode = 0;
        if (GetConsoleMode(hOut, &mode)) {
            mode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
            SetConsoleMode(hOut, mode);
        }
    }
    // Set code page to UTF-8 for proper block character rendering
    SetConsoleOutputCP(CP_UTF8);
#endif
}

void ScreenCommon::clearScreen() const {
#ifdef WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

void ScreenCommon::showTopBanner(const std::string& currentScreen) const {
    clearScreen();
    
    // PSCORE banner with Claude Code CLI style box-drawing characters
    std::cout << std::endl;
    if (ui::Theme::enabled()) {
        std::cout << ui::Theme::bold() << ui::Theme::brightGreen();
    }
    
    std::cout << "            ██████╗ ███████╗ ██████╗ ██████╗ ██████╗ ███████╗" << std::endl;
    std::cout << "            ██╔══██╗██╔════╝██╔════╝██╔═══██╗██╔══██╗██╔════╝" << std::endl;
    std::cout << "            ██████╔╝███████╗██║     ██║   ██║██████╔╝█████╗  " << std::endl;
    std::cout << "            ██╔═══╝ ╚════██║██║     ██║   ██║██╔══██╗██╔══╝  " << std::endl;
    std::cout << "            ██║     ███████║╚██████╗╚██████╔╝██║  ██║███████╗" << std::endl;
    std::cout << "            ╚═╝     ╚══════╝ ╚═════╝ ╚═════╝ ╚═╝  ╚═╝╚══════╝" << std::endl;
    
    if (ui::Theme::enabled()) {
        std::cout << ui::Theme::reset();
    }
    std::cout << std::endl;
    
    // Version and current screen in a clean darkwire style
    if (ui::Theme::enabled()) {
        std::cout << ui::Theme::dim();
    }
    
    // Create a horizontal line with version and current screen
    std::string versionStr = "v" + std::string(getCoreVersion());
    std::string separator = "--------------------------------------------------------------------------------";
    
    // Center the current screen and version info
    std::cout << separator << std::endl;
    
    if (ui::Theme::enabled()) {
        std::cout << ui::Theme::reset() << ui::Theme::brightGreen();
    }
    
    // Format: [CURRENT_SCREEN]  [VERSION]  [BUSINESS_MENUS]
    std::cout << "[" << currentScreen << "]";
    
    if (ui::Theme::enabled()) {
        std::cout << ui::Theme::reset() << ui::Theme::dim();
    }
    
    std::cout << "  [" << versionStr << "]";
    
    if (ui::Theme::enabled()) {
        std::cout << ui::Theme::reset() << ui::Theme::brightGreen();
    }
    
    std::cout << "  [PERSONAL INFO]  [EMPLOYEES]  [INVENTORY]  [CUSTOMERS]  [ACCOUNTING]" << std::endl;
    
    if (ui::Theme::enabled()) {
        std::cout << ui::Theme::reset() << ui::Theme::dim();
    }
    
    std::cout << separator << std::endl;
    
    if (ui::Theme::enabled()) {
        std::cout << ui::Theme::reset();
    }
    
    std::cout << std::endl;
}

void ScreenCommon::printTitleText(const std::string& text, bool showBorders) const {
    const Indent indents = calculateIndents(VerticalAlignment::CENTER,
                                            defines::SCREEN_WIDTH, text);
    // Simplified border handling
    const char left = (showBorders ? defines::BORDER_CHARACTER_1 : ' ');
    const char right = (showBorders ? defines::BORDER_CHARACTER_1 : ' ');
    std::cout << left << indents.start << text << indents.end << right << std::endl;
}

void ScreenCommon::printItemText(const std::string& label, const std::string& item) const {
    if (item.empty()) {
        // Don't show anything if item is empty
        return;
    }
    // Simplified with minimal theming
    if (ui::Theme::enabled()) {
        std::cout << ui::Theme::dim();
    }
    std::cout << std::left << std::setw(defines::LABEL_WIDTH) << label;
    if (ui::Theme::enabled()) {
        std::cout << ui::Theme::reset() << ui::Theme::cyan();
    }
    std::cout << defines::LABEL_BOUNDARY;
    if (ui::Theme::enabled()) {
        std::cout << ui::Theme::reset();
    }
    std::cout << " " << item << std::endl;
}

void ScreenCommon::printColumns(const std::vector<std::string>& columns,
                                bool isHeader, bool showColumnBorders) const {
    const unsigned int columnWidth = defines::SCREEN_WIDTH / columns.size();
    unsigned int modulo = defines::SCREEN_WIDTH % columns.size();
    if (isHeader) {
        // Print upper border
        if (ui::Theme::enabled()) std::cout << ui::Theme::use(ui::Theme::cyan());
        printHorizontalBorder(defines::BORDER_CHARACTER_2);
        if (ui::Theme::enabled()) std::cout << ui::Theme::use(ui::Theme::reset());
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
        if (showColumnBorders || (i == 0)) {
            if (ui::Theme::enabled()) std::cout << ui::Theme::use(ui::Theme::cyan());
            std::cout << defines::BORDER_CHARACTER_3;
            if (ui::Theme::enabled()) std::cout << ui::Theme::use(ui::Theme::reset());
        } else {
            std::cout << ' ';
        }
        if (isHeader && ui::Theme::enabled()) std::cout << ui::Theme::use(ui::Theme::bold());
        std::cout << indents.start << columns[i] << indents.end
                  << (ui::Theme::enabled() ? ui::Theme::use(ui::Theme::reset()) : "")
                  // If columns.size() is odd, do +1 space for each column width
                  << [&modulo]() { return modulo > 0 ? (modulo--, " ") : ""; }();
    }
    // End column border
    if (ui::Theme::enabled()) std::cout << ui::Theme::use(ui::Theme::cyan());
    std::cout << defines::BORDER_CHARACTER_3 << std::endl;
    if (ui::Theme::enabled()) std::cout << ui::Theme::use(ui::Theme::reset());
    if (isHeader) {
        // Print bottom border
        if (ui::Theme::enabled()) std::cout << ui::Theme::use(ui::Theme::cyan());
        printHorizontalBorder(defines::BORDER_CHARACTER_2);
        if (ui::Theme::enabled()) std::cout << ui::Theme::use(ui::Theme::reset());
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
    if (ui::Theme::enabled()) std::cout << ui::Theme::use(ui::Theme::red());
    std::cout << "Invalid inputs:" << std::endl;
    if (ui::Theme::enabled()) std::cout << ui::Theme::use(ui::Theme::reset());
    for (const std::string& error : errors) {
        if (ui::Theme::enabled()) std::cout << ui::Theme::use(ui::Theme::red());
        std::cout << "- ";
        if (ui::Theme::enabled()) std::cout << ui::Theme::use(ui::Theme::reset());
        std::cout << error << std::endl;
    }
    // Let the user confirm after viewing the validation results
    if (ui::Theme::enabled()) std::cout << ui::Theme::use(ui::Theme::dim());
    std::cout << "Press [Enter] to update fields..." << std::endl;
    if (ui::Theme::enabled()) std::cout << ui::Theme::use(ui::Theme::reset());
    std::cin.ignore();
    std::cin.get();
}

std::string ScreenCommon::getInput(const std::string& label, unsigned int maxSize) const {
    std::string userInput;
    do {
        // Simplified input prompt with theming
        if (ui::Theme::enabled()) {
            std::cout << ui::Theme::dim();
        }
        std::cout << std::left << std::setw(defines::LABEL_WIDTH) << label;
        if (ui::Theme::enabled()) {
            std::cout << ui::Theme::reset() << ui::Theme::cyan();
        }
        std::cout << defines::LABEL_BOUNDARY << " ";
        if (ui::Theme::enabled()) {
            std::cout << ui::Theme::reset();
        }
        
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
        if (ui::Theme::enabled()) std::cout << ui::Theme::use(ui::Theme::dim());
        std::cout << std::left << std::setw(defines::LABEL_WIDTH)
              << label;
        if (ui::Theme::enabled()) std::cout << ui::Theme::use(ui::Theme::reset())
                            << ui::Theme::use(ui::Theme::cyan());
        std::cout << defines::LABEL_BOUNDARY << " ";
        if (ui::Theme::enabled()) std::cout << ui::Theme::use(ui::Theme::reset());
        std::cin >> userInput;
        std::transform(userInput.begin(), userInput.end(), userInput.begin(),
                       [](unsigned char c){ return std::tolower(c); });
    } while (userInput != "y" && userInput != "n");
    return userInput;
}

void ScreenCommon::inputArea(std::function<void(const std::string&)> func,
                             const std::string& label) const {
    func(SCREENCOMMON().getInput(label));
}

const std::string ScreenCommon::getUpdateField(const std::vector<std::string>& fields) const {
    uint8_t index = 0;
    do {
        // Ask the index from the user
        std::string userInput = SCREENCOMMON().getInput("Input the data [number] to edit");
        if (utility::isNumber(userInput)) {
            index =  std::stoi(userInput);
            break;
        }
    } while (1);  // Keep asking until a number is inputted
    // Make sure this index is valid
    if ((index == 0) || (index > fields.size())) {
        return "";
    }
    // Vector is a 0-based index
    return fields[index - 1];
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
    // Simple hardcoded return for debugging
    return std::string("0.4.12");
}

}  // namespace screen