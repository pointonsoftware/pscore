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
#include <vector>
#include "interface/employeemgmtiface.hpp"

// Entity
#include <entity/user.hpp>

namespace domain {
namespace empmgmt {

class EmployeeMgmtController : public EmployeeMgmtControlInterface {
 public:
    explicit EmployeeMgmtController(const std::shared_ptr<EmployeeMgmtDataInterface>& data,
                                    const std::shared_ptr<EmployeeMgmtViewInterface>& view);
    ~EmployeeMgmtController() = default;

    std::vector<entity::Employee> list() override;
    entity::User get(const std::string& userID) override;
    USERSMGMTSTATUS save(const entity::User& userID) override;
    USERSMGMTSTATUS remove(const std::string& id) override;

 private:
    std::shared_ptr<EmployeeMgmtDataInterface> mDataProvider;
    std::shared_ptr<EmployeeMgmtViewInterface> mView;
};

}  // namespace empmgmt
}  // namespace domain

#endif  // CORE_DOMAIN_EMPLOYEEMGMT_EMPLOYEECONTROLLER_HPP_