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
#ifndef ORCHESTRA_DATAMANAGER_EMPLOYEEDATA_HPP_
#define ORCHESTRA_DATAMANAGER_EMPLOYEEDATA_HPP_
#include <string>
#include <vector>
#include <domain/employeemgmt/interface/employeemgmtdataif.hpp>

namespace dataprovider {
namespace empmgmt {

class EmployeeDataProvider : public domain::empmgmt::EmployeeMgmtDataInterface {
 public:
    EmployeeDataProvider() = default;
    virtual ~EmployeeDataProvider() = default;

    std::vector<entity::Employee> getEmployees() override;
    entity::User getUserData(const std::string& employeeID) override;
    void create(const entity::Employee& employee) override;
    void create(const entity::User& user) override;
    void update(const entity::Employee& employee) override;
    void update(const entity::User& user) override;
    void removeWithID(const std::string& employeeID) override;

 private:
    // Used to fill the employee object with other details
    void fillEmployeeDetails(entity::Employee* employee) const;
    // Used to write the employee address, contact and other details to DB
    void writeEmployeeDetails(const entity::Employee& employee) const;
};

}  // namespace empmgmt
}  // namespace dataprovider
#endif  // ORCHESTRA_DATAMANAGER_EMPLOYEEDATA_HPP_
