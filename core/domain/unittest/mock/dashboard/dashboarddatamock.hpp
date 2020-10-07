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
#ifndef CORE_DOMAIN_UNITTEST_MOCK_DASHBOARD_DASHBOARDDATAMOCK_HPP_
#define CORE_DOMAIN_UNITTEST_MOCK_DASHBOARD_DASHBOARDDATAMOCK_HPP_
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <domain/dashboard/interface/dashboarddataif.hpp>
#include <entity/user.hpp>

namespace domain {
namespace dashboard {

class DashboardDataMock : public DashboardDataInterface {
 public:
    DashboardDataMock() = default;
    ~DashboardDataMock() = default;

    MOCK_METHOD(entity::User, getUserByID, (const std::string& userID));
};

}  // namespace dashboard
}  // namespace domain

#endif  // CORE_DOMAIN_UNITTEST_MOCK_DASHBOARD_DASHBOARDDATAMOCK_HPP_