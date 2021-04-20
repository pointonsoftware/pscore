/**************************************************************************************************
*                                            PSCORE                                               *
*                               Copyright (C) 2021 Pointon Software                               *
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
#ifndef CORE_DOMAIN_UNITTEST_MOCK_ACCOUNTING_ACCOUNTINGDATAMOCK_HPP_
#define CORE_DOMAIN_UNITTEST_MOCK_ACCOUNTING_ACCOUNTINGDATAMOCK_HPP_
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <string>
#include <vector>

#include <domain/accounting/interface/accountingdataif.hpp>
#include <entity/sale.hpp>
#include <entity/saleitem.hpp>

namespace domain {
namespace accounting {

class AccountingDataMock : public AccountingDataInterface {
 public:
    AccountingDataMock() = default;
    ~AccountingDataMock() = default;
    MOCK_METHOD(std::vector<entity::Sale>, getSales, (const std::string& startDate,
                                                      const std::string& endDate));
    MOCK_METHOD(std::vector<entity::SaleItem>, getSaleDetails, (const std::string& transactionID));
};

}  // namespace accounting
}  // namespace domain

#endif  // CORE_DOMAIN_UNITTEST_MOCK_ACCOUNTING_ACCOUNTINGDATAMOCK_HPP_