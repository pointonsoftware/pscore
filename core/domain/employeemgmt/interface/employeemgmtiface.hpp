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

enum class EMPLMGMTSTATUS {
    SUCCESS       = 0x00,
    FAILED        = 0x01,
    UNINITIALIZED = 0x02,
    NOT_FOUND     = 0x03
};

struct SaveEmployeeData {
    // [in]
    const entity::Employee& employee;
    // [in] Fill only if employee is a system-user
    const std::string& PIN;
    // [out]
    std::map<std::string, std::string>* validationResult;
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
     * Returns the info of the requested employee
    */
    virtual entity::Employee getEmployee(const std::string& employeeID) = 0;
    /*!
    * Returns the info of the requested user
    * @param [in] - employeeID of the user
    */
    virtual entity::User getUser(const std::string& employeeID) = 0;
    /*!
     * The caller must provide the employeeID.
     * To create an employee, the employeeID must not exist from the database.
     * To update an employee, use an employee object retrieved through list() or get() call.
     * @param [out] - map of [field, error message]
     *
     * Note: This will reset the map container
    */
    virtual EMPLMGMTSTATUS save(const SaveEmployeeData& employeeData) = 0;
    /*!
     * Deletes the employee and user
    */
    virtual EMPLMGMTSTATUS remove(const std::string& employeeID) = 0;
    /*!
     * Find the employees with first and last name
    */
    virtual std::vector<entity::Employee> findByName(const std::string& fname,
                                                     const std::string& lname) = 0;
};

typedef std::shared_ptr<EmployeeMgmtDataInterface> EmpMgmtDataPtr;
typedef std::shared_ptr<EmployeeMgmtViewInterface> EmpMgmtViewPtr;
typedef std::unique_ptr<EmployeeMgmtControlInterface> EmpMgmtControllerPtr;

// Lib APIs
extern "C" CORE_API EmpMgmtControllerPtr createEmployeeMgmtModule
                    (const EmpMgmtDataPtr& data, const EmpMgmtViewPtr& view);

}  // namespace empmgmt
}  // namespace domain

#endif  // CORE_DOMAIN_EMPLOYEEMGMT_INTERFACE_EMPLOYEEMGMTIFACE_HPP_