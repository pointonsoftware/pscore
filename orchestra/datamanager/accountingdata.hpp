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
#ifndef ORCHESTRA_DATAMANAGER_ACCOUNTINGDATA_HPP_
#define ORCHESTRA_DATAMANAGER_ACCOUNTINGDATA_HPP_
#include <string>
#include <vector>
#include <datetime/datetime.hpp>
#include <domain/accounting/interface/accountingdataif.hpp>

namespace dataprovider {
namespace accounting {

class AccountingDataProvider : public domain::accounting::AccountingDataInterface {
 public:
    AccountingDataProvider() = default;
    virtual ~AccountingDataProvider() = default;

    std::vector<entity::Sale> getSales(const std::string& startDate,
                                       const std::string& endDate) override;

    std::vector<entity::SaleItem> getSaleDetails(const std::string& transactionID) override;
 private:
    utility::DateTimeComparator mDateTimeComparator;
};

}  // namespace accounting
}  // namespace dataprovider
#endif  // ORCHESTRA_DATAMANAGER_ACCOUNTINGDATA_HPP_
