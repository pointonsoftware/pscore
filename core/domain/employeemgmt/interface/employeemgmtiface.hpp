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
#ifndef CORE_DOMAIN_EMPLOYEEMGMT_INTERFACE_EMPLOYEEMGMTIFACE_HPP_
#define CORE_DOMAIN_EMPLOYEEMGMT_INTERFACE_EMPLOYEEMGMTIFACE_HPP_
#include <memory>
#include <string>
#include <map>
#include <vector>
#include "employeemgmtdataif.hpp"
#include "employeemgmtviewif.hpp"
#include <domain/librarycommon.hpp>
#include <entity/user.hpp>

namespace domain {
namespace empmgmt {

enum class USERSMGMTSTATUS {
    SUCCESS       = 0,
    FAILED        = 1,
    UNINITIALIZED = 2,
    NOT_FOUND     = 3
};

struct SaveEmployeeData {
    // [in]
    const entity::Employee& employee;
    // [out]
    std::map<std::string, std::string>* validationResult;

    // [in] Fill only if employee is a system-user
    const std::string& displayName;
    const std::string& PIN;
};

class EmployeeMgmtControlInterface {
 public:
    EmployeeMgmtControlInterface() = default;
    virtual ~EmployeeMgmtControlInterface() = default;

    /*!
     * Gets the list of all employees
    */
    virtual std::vector<entity::Employee> list() = 0;
    /*!
     * Returns the info of the requested user
    */
    virtual entity::Employee get(const std::string& id) = 0;
    /*!
     * Creates the employee if not exists, otherwise will update the employee info
     * - param [out]- map of [field, error message]
    */
    virtual USERSMGMTSTATUS save(const SaveEmployeeData& employeeData) = 0;
    /*!
     * Deletes the user
    */
    virtual USERSMGMTSTATUS remove(const std::string& userID) = 0;
    /*!
     * Find the employees with first and last name
    */
    virtual std::vector<entity::Employee> findByName(const std::string& fname,
                                                     const std::string& lname) = 0;
};

// Lib APIs
extern "C" CORE_API std::unique_ptr<EmployeeMgmtControlInterface> createEmployeeMgmtModule(
                    const std::shared_ptr<EmployeeMgmtDataInterface>& data,
                    const std::shared_ptr<EmployeeMgmtViewInterface>& view);

}  // namespace empmgmt
}  // namespace domain

#endif  // CORE_DOMAIN_EMPLOYEEMGMT_INTERFACE_EMPLOYEEMGMTIFACE_HPP_