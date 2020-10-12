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
#ifndef APPLICATION_SCREEN_COMMON_HPP_
#define APPLICATION_SCREEN_COMMON_HPP_
#include "screencommon.hpp"
#include <cstdlib>
#include <iostream>
#include <iomanip>
#include "screendefines.hpp"

namespace screen {

void ScreenCommon::clearScreen() const {
#ifdef __WIN32__
    std::system("cls");
#else
    std::system("clear");
#endif
}

const std::string ScreenCommon::horizontalBorder() const {
    return "*********************************************************************************";
}

void ScreenCommon::printTitleText(const std::string& text) const {
    const Indent indents = calculateIndents(text);
    std::cout << "*" << indents.start << text << indents.end << "*" << std::endl;
}

void ScreenCommon::printItemText(const std::string& label, const std::string& item) const {
    std::cout << std::left << std::setw(defines::LABEL_WIDTH)
              << label  << defines::LABEL_BOUNDARY << " "
              << item   << std::endl;
}

void ScreenCommon::showTopBanner(const std::string& currentScreen) const {
    clearScreen();
    std::cout << horizontalBorder() << std::endl;
    printTitleText("");
    printTitleText(std::string("---- CORE "+ std::string(VERSION) +" ----"));
    printTitleText("");
    printTitleText("Console  Application");
    printTitleText("");
    printTitleText("Enter [x] if you want to exit");
    std::cout << horizontalBorder() << std::endl;
    printTitleText(currentScreen);
    std::cout << horizontalBorder() << std::endl;
}

ScreenCommon::Indent ScreenCommon::calculateIndents(const std::string& text) const {
    Indent indents;
    indents.start = std::string((defines::SCREEN_WIDTH - text.size()) / 2, ' ');
    indents.end = indents.start;
    if (!(text.size() % 2)) {
        indents.end = indents.start.substr(0, indents.start.size()-1);
    }
    return indents;
}

}  // namespace screen
#endif  // APPLICATION_SCREEN_COMMON_HPP_