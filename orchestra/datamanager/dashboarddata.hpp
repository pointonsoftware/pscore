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
#ifndef ORCHESTRA_DATAMANAGER_DASHBOARDDATA_HPP_
#define ORCHESTRA_DATAMANAGER_DASHBOARDDATA_HPP_
#include <string>
#include <domain/dashboard/interface/dashboarddataif.hpp>

namespace dataprovider {
namespace dashboard {

class DashboardDataProvider : public domain::dashboard::DashboardDataInterface {
 public:
    DashboardDataProvider() = default;
    virtual ~DashboardDataProvider() = default;
    entity::User getUserByID(const std::string& userID) override;
};

}  // namespace dashboard
}  // namespace dataprovider
#endif  // ORCHESTRA_DATAMANAGER_DASHBOARDDATA_HPP_
