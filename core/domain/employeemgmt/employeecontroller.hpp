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
#ifndef CORE_DOMAIN_EMPLOYEEMGMT_EMPLOYEECONTROLLER_HPP_
#define CORE_DOMAIN_EMPLOYEEMGMT_EMPLOYEECONTROLLER_HPP_
#include <memory>
#include <string>
#include <map>
#include <vector>
#include "interface/employeemgmtiface.hpp"
#include <domain/common/basecontroller.hpp>
// Entity
#include <entity/employee.hpp>
#include <entity/user.hpp>

namespace domain {
namespace empmgmt {

typedef std::map<std::string, std::string> ValidationErrors;

class EmployeeMgmtController : public EmployeeMgmtControlInterface,
                               public BaseController<EmployeeMgmtDataInterface,
                                                     EmployeeMgmtViewInterface,
                                                     entity::Employee> {
 public:
    explicit EmployeeMgmtController(const EmpMgmtDataPtr& data,
                                    const EmpMgmtViewPtr& view);
    ~EmployeeMgmtController() = default;

    std::vector<entity::Employee> list() override;
    entity::Employee getEmployee(const std::string& employeeID) override;
    entity::User getUser(const std::string& employeeID) override;
    EMPLMGMTSTATUS save(const SaveEmployeeData& employeeData) override;
    EMPLMGMTSTATUS remove(const std::string& employeeID) override;
    std::vector<entity::Employee> findByName(const std::string& fname,
                                             const std::string& lname) override;

 private:
    ValidationErrors validateDetails(const entity::Employee& employee) const;

    void create(const SaveEmployeeData& data);
    void createUser(const entity::Employee& employee, const std::string& pin) const;
    void update(const SaveEmployeeData& data);
};

}  // namespace empmgmt
}  // namespace domain

#endif  // CORE_DOMAIN_EMPLOYEEMGMT_EMPLOYEECONTROLLER_HPP_