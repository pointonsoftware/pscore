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

// Entity
#include <entity/user.hpp>

namespace domain {
namespace empmgmt {

typedef std::map<std::string, std::string> ValidationErrors;

class EmployeeMgmtController : public EmployeeMgmtControlInterface {
 public:
    explicit EmployeeMgmtController(const std::shared_ptr<EmployeeMgmtDataInterface>& data,
                                    const std::shared_ptr<EmployeeMgmtViewInterface>& view);
    ~EmployeeMgmtController() = default;

    std::vector<entity::Employee> list() override;
    entity::Employee get(const std::string& id) override;
    USERSMGMTSTATUS save(const SaveEmployeeData& employeeData) override;
    USERSMGMTSTATUS remove(const std::string& id) override;
    std::vector<entity::Employee> findByName(const std::string& fname,
                                             const std::string& lname) override;

 private:
    std::shared_ptr<EmployeeMgmtDataInterface> mDataProvider;
    std::shared_ptr<EmployeeMgmtViewInterface> mView;
    std::vector<entity::Employee> mCachedList;  // List of employees

    bool isExists(const std::string& id);
    std::vector<entity::Employee>::iterator find(const std::string& id);
    bool isInterfaceInitialized() const;
    ValidationErrors validateDetails(const entity::Employee& employee) const;
    void dumpValidationResult(const ValidationErrors& validationErrors) const;

    USERSMGMTSTATUS create(const entity::Employee& employee) const;
    USERSMGMTSTATUS update(const entity::Employee& employee) const;
};

}  // namespace empmgmt
}  // namespace domain

#endif  // CORE_DOMAIN_EMPLOYEEMGMT_EMPLOYEECONTROLLER_HPP_