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
#ifndef ORCHESTRA_APPLICATION_UTILITY_UI_THEME_HPP_
#define ORCHESTRA_APPLICATION_UTILITY_UI_THEME_HPP_

#include <cstdlib>
#include <string>
#include <cctype>

namespace screen {
namespace ui {

// Header-only minimal theming helpers for console rendering
struct Theme {
    // Toggle theme via env var: PS_THEME=classic disables colors
    static bool enabled() {
        const char* val = std::getenv("PS_THEME");
        if (!val) return true;  // default: on
        std::string v(val);
        for (auto& c : v) c = static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        return !(v == "classic" || v == "off" || v == "0" || v == "disable" || v == "disabled");
    }

    // ANSI sequences
    static const char* reset() { return "\033[0m"; }
    static const char* bold() { return "\033[1m"; }
    static const char* dim() { return "\033[2m"; }
    static const char* cyan() { return "\033[36m"; }      // primary accent
    static const char* magenta() { return "\033[35m"; }   // secondary accent
    static const char* red() { return "\033[31m"; }
    static const char* yellow() { return "\033[33m"; }
    static const char* white() { return "\033[37m"; }
    static const char* green() { return "\033[32m"; }     // standard green
    static const char* brightGreen() { return "\033[92m"; }  // bright green

    // Convenience wrappers: if disabled, return empty string to avoid escape output
    static const char* use(const char* code) { return enabled() ? code : ""; }
};

}  // namespace ui
}  // namespace screen

#endif  // ORCHESTRA_APPLICATION_UTILITY_UI_THEME_HPP_
