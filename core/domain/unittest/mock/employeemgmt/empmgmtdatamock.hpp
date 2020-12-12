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
#ifndef CORE_DOMAIN_UNITTEST_MOCK_EMPLOYEEMGMT_EMPMGMTDATAMOCK_HPP_
#define CORE_DOMAIN_UNITTEST_MOCK_EMPLOYEEMGMT_EMPMGMTDATAMOCK_HPP_
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>
#include <domain/employeemgmt/interface/employeemgmtdataif.hpp>
#include <entity/employee.hpp>
#include <entity/user.hpp>

namespace domain {
namespace empmgmt {

class EmployeeMgmtDataMock : public EmployeeMgmtDataInterface {
 public:
    EmployeeMgmtDataMock() = default;
    ~EmployeeMgmtDataMock() = default;

    MOCK_METHOD(std::vector<entity::Employee>, getEmployees, ());
    MOCK_METHOD(void, create, (const entity::Employee&));
    MOCK_METHOD(void, create, (const entity::User&));
    MOCK_METHOD(void, update, (const entity::Employee&));
    MOCK_METHOD(void, update, (const entity::User&));
    MOCK_METHOD(void, removeWithID, (const std::string&));
};

}  // namespace empmgmt
}  // namespace domain

#endif  // CORE_DOMAIN_UNITTEST_MOCK_EMPLOYEEMGMT_EMPMGMTDATAMOCK_HPP_