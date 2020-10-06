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
#ifndef CORE_DOMAIN_UNITTEST_MOCK_DASHBOARD_DASHBOARDVIEWMOCK_HPP_
#define CORE_DOMAIN_UNITTEST_MOCK_DASHBOARD_DASHBOARDVIEWMOCK_HPP_
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <domain/dashboard/interface/dashboardviewif.hpp>

namespace domain {
namespace dashboard {

class DashboardViewMock : public DashboardViewInterface {
 public:
    DashboardViewMock() = default;
    ~DashboardViewMock() = default;

    MOCK_METHOD(void, showUserNotFound, ());
    MOCK_METHOD(void, showInvalidOptionPopup, ());
    MOCK_METHOD(void, showDataNotReadyScreen, ());
};

}  // namespace dashboard
}  // namespace domain

#endif  // CORE_DOMAIN_UNITTEST_MOCK_DASHBOARD_DASHBOARDVIEWMOCK_HPP_