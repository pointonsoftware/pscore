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
#ifndef CORE_DOMAIN_UNITTEST_MOCK_CUSTOMERMGMT_CUSTOMERMGMTVIEWMOCK_HPP_
#define CORE_DOMAIN_UNITTEST_MOCK_CUSTOMERMGMT_CUSTOMERMGMTVIEWMOCK_HPP_
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <domain/customermgmt/interface/customermgmtviewif.hpp>

namespace domain {
namespace customermgmt {

class CustomerManagementViewMock : public CustomerManagementViewInterface {
 public:
    CustomerManagementViewMock() = default;
    ~CustomerManagementViewMock() = default;

    MOCK_METHOD(void, showListIsEmptyPopup, ());
    MOCK_METHOD(void, showDataNotReadyScreen, ());
    MOCK_METHOD(void, showSuccessfullyRemoved, (const std::string& customerName));
};

}  // namespace customermgmt
}  // namespace domain

#endif  // CORE_DOMAIN_UNITTEST_MOCK_CUSTOMERMGMT_CUSTOMERMGMTVIEWMOCK_HPP_