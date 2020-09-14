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
#include "authcontroller.hpp"

namespace domain {
namespace authentication {

AuthController::AuthController(std::unique_ptr<AuthViewIface>&& view,
                               std::unique_ptr<AuthDataProviderIface>&& dataprovider)
: mView(std::move(view)), mDataProvider(std::move(dataprovider)) {
    // Empty for now
}

bool AuthController::login(const std::string& pin) {
    // Check if pin is empty
    // Check if pin is numeric
    // Call authenticate
    return true;
}

status::General AuthController::authenticate(const std::string& pin) {
    // Check if dataprovider is ready; else throw
    // Check pin in dataprovider
    return status::General::SUCCESS;
}

}  // namespace authentication
}  // namespace domain