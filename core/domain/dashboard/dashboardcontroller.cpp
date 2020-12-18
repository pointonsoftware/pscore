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
#include <general.hpp>  // pscore utility
#include <logger/loghelper.hpp>

namespace domain {
namespace dashboard {

DashboardController::DashboardController(const std::shared_ptr<DashboardDataInterface>& data,
                                         const std::shared_ptr<DashboardViewInterface>& view) {
    if((data == nullptr) || (view == nullptr)) {
        throw std::invalid_argument("Received a nulltpr argument");
    }
    mDataProvider = data;
    mView = view;
}

void DashboardController::setCurrentUserId(const std::string& userID) {
    if (!userID.empty()) {
        LOG_INFO("Setting current user ID to: %s", userID.c_str());
        mCurrentUserID = utility::toUpper(userID);
    }
}

entity::User DashboardController::getCurrentUser() {
    LOG_DEBUG("Getting current user info");
    if (mCurrentUserID.empty()) {
        LOG_ERROR("UserID was not set");
        // Todo (spec), do we need a more specific popup here?
        mView->showUserNotFound();
        return entity::User();
    }
    // Retrieve the userinfo from db using userID
    entity::User userInfo;
    if (getUserData(&userInfo) != DASHSTATUS::SUCCESS) {
        mView->showDataNotReadyScreen();
        return entity::User();
    }
    // Validate user info
    if (!isUserValid(userInfo)) {
        LOG_ERROR("UserID %s was not found", mCurrentUserID.c_str());
        mView->showUserNotFound();
        return entity::User();
    }

    LOG_INFO("Current user with ID: %s was found", mCurrentUserID.c_str());
    return userInfo;
}

DASHSTATUS DashboardController::getUserData(entity::User* container) const {
    if (!container) {
        LOG_ERROR("Invalid user argument");
        return DASHSTATUS::FAILED;
    }
    LOG_DEBUG("Retrieving user data");
    // todo (xxx) : Check if dataprovider is ready; else throw
    *container = mDataProvider->getUserByID(mCurrentUserID);
    return DASHSTATUS::SUCCESS;
}

entity::Employee DashboardController::getUserDetails(const entity::User& user) {
    LOG_DEBUG("Getting employee details");
    // Validate user info
    if (!isUserValid(user)) {
        LOG_ERROR("UserID %s was not found", mCurrentUserID.c_str());
        mView->showUserNotFound();
        return entity::Employee();
    }
    if (user.employeeID().empty()) {
        LOG_ERROR("User is not an employee");
        mView->showUserNotFound();
        return entity::Employee();
    }
    // Retrieve employee data
    entity::Employee temp;
    if (getEmployeeData(user.employeeID(), &temp) != DASHSTATUS::SUCCESS) {
        mView->showDataNotReadyScreen();
        return entity::Employee();
    }
    if (temp.employeeID().empty()) {
        LOG_ERROR("Failed to retrieve employee data for user %s", mCurrentUserID.c_str());
        mView->showUserNotFound();
        return entity::Employee();
    }
    return temp;
}

DASHSTATUS DashboardController::getEmployeeData(const std::string& employeeID,
                                                entity::Employee* container) const {
    if (!container) {
        LOG_ERROR("Invalid user argument");
        return DASHSTATUS::FAILED;
    }
    LOG_DEBUG("Retrieving employee data");
    // todo (xxx) : Check if dataprovider is ready; else throw
    *container = mDataProvider->getEmployeeInformation(employeeID);
    return DASHSTATUS::SUCCESS;
}

bool DashboardController::isUserValid(const entity::User& userInfo) const {
    LOG_DEBUG("Validating user data");
    // If userID is empty, that means the user data was not initialized
    return !userInfo.userID().empty();
}

std::unique_ptr<DashboardControlInterface> createDashboardModule(
            const std::shared_ptr<DashboardDataInterface>& data,
            const std::shared_ptr<DashboardViewInterface>& view) {
    return std::make_unique<DashboardController>(data, view);
}

}  // namespace dashboard
}  // namespace domain

