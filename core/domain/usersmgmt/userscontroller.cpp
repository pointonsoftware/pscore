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
#include "userscontroller.hpp"
#include <memory>
#include <logger/loghelper.hpp>

namespace domain {
namespace usersmgmt {

UsersMgmtController::UsersMgmtController() {
    // empty for now
}

std::vector<entity::User> UsersMgmtController::list() {
    // PCOR-34
    return {};
}

entity::User UsersMgmtController::get(const std::string& userID) {
    // PCOR-36
    return entity::User();
}

USERSMGMTSTATUS UsersMgmtController::save(const entity::User& userID) {
    // PCOR-32
    return USERSMGMTSTATUS::SUCCESS;
}

USERSMGMTSTATUS UsersMgmtController::remove(const std::string& userID) {
    // PCOR-33
    return USERSMGMTSTATUS::SUCCESS;
}

std::unique_ptr<UsersMgmtControlInterface> createUsersMgmtModule() {
    return std::make_unique<UsersMgmtController>();
}

}  // namespace usersmgmt
}  // namespace domain
