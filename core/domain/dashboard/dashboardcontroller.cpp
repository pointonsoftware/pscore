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

DashboardController::DashboardController(const std::shared_ptr<DashboardDataInterface>& data,
                                         const std::shared_ptr<DashboardViewInterface>& view)
: mDataProvider(data), mView(view), mCurrentUserID("") {
    // empty for now
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
    // Retrieve the userinfo from db using userID
    entity::User userInfo;
    if (getCurrentUserInfo(&userInfo) != DASHSTATUS::SUCCESS) {
        mView->showDataNotReadyScreen();
        return entity::User();
    }
    // Validate user info
    if (!isUserValid(userInfo)) {
        LOG_WARN("UserID %s was not found", mCurrentUserID.c_str());
        mView->showUserNotFound();
        return entity::User();
    }
    return userInfo;
}

DASHSTATUS DashboardController::getCurrentUserInfo(entity::User* userInfoContainer) const {
    if (!userInfoContainer) {
        LOG_ERROR("Invalid user argument");
        return DASHSTATUS::FAILED;
    }
    if (!mDataProvider) {
        LOG_ERROR("Dataprovider is not initialized");
        return DASHSTATUS::UNINITIALIZED;
    }
    // todo (xxx) : Check if dataprovider is ready; else throw
    *userInfoContainer = mDataProvider->getUserByID(mCurrentUserID);
    return DASHSTATUS::SUCCESS;
}

bool DashboardController::isUserValid(const entity::User& userInfo) const {
    // If employeeID is empty, that means the user data was not initialized
    return !userInfo.getEmployeeID().empty();
}

std::unique_ptr<DashboardControlInterface> createDashboardModule(
            const std::shared_ptr<DashboardDataInterface>& data,
            const std::shared_ptr<DashboardViewInterface>& view) {
    return std::make_unique<DashboardController>(data, view);
}

}  // namespace dashboard
}  // namespace domain

