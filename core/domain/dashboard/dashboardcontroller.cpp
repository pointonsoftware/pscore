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
#include "dashboardcontroller.hpp"
#include <iostream>
#include <memory>
#include <string>
#include <logger/loghelper.hpp>

namespace domain {
namespace dashboard {

DashboardController::DashboardController(const std::shared_ptr<DashboardViewInterface>& view)
: mView(view), mCurrentUserID("") {
    // empty for now
}

void DashboardController::PrintUser() {
    std::cout << "Hi " << mCurrentUserID << ", what do you want to do today?" << std::endl;
}

void DashboardController::setCurrentUserId(const std::string& userID) {
    if (!userID.empty()) {
        mCurrentUserID = userID;
    }
}

entity::User DashboardController::getCurrentUserInfo() {
    // Make sure view is valid
    if (!mView) {
        LOG_ERROR("View is not initialized");
        return entity::User();
    }

    if (mCurrentUserID.empty()) {
        LOG_ERROR("UserID was not set.");
        // Todo (spec), do we need a more specific popup here?
        mView->showUserNotFound();
        return entity::User();
    }

    // Todo, retrieve the userinfo from db using userID
    // dashboardDataProvider->getUserInfo(mUserID);
    const entity::User temp = []() {
        // todo (data): find the user info
        return entity::User();
    }();

    // Validate user info
    if (!isUserValid(temp)) {
        LOG_WARN("UserID %s was not found", mCurrentUserID.c_str());
        mView->showUserNotFound();
        return entity::User();
    }

    return temp;
}

bool DashboardController::isUserValid(const entity::User& userInfo) const {
    // If default pin is found, that means the user data was not initialized
    return userInfo.pin().find(entity::User::DEFAULT_PIN) == std::string::npos;
}

std::unique_ptr<DashboardControlInterface> createDashboardModule(
            const std::shared_ptr<DashboardViewInterface>& view) {
    return std::make_unique<DashboardController>(view);
}

}  // namespace dashboard
}  // namespace domain

