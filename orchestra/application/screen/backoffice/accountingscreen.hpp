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
#ifndef ORCHESTRA_APPLICATION_SCREEN_BACKOFFICE_ACCOUNTINGSCREEN_HPP_
#define ORCHESTRA_APPLICATION_SCREEN_BACKOFFICE_ACCOUNTINGSCREEN_HPP_
#include <string>
#include <vector>
// Core
#include <domain/accounting/interface/accountingviewif.hpp>
#include <domain/accounting/interface/accountingiface.hpp>
#include <domain/common/types.hpp>
// Screens
#include "backofficescreenbase.hpp"
#include <fieldhelper.hpp>
#include <screeniface.hpp>
#include <tablehelper.hpp>

namespace screen {
namespace backoffice {

class DomainGraphMemberWrapper;  // see definition at the end of this file

class AccountingScreen : public screen::ScreenInterface,
                    public BackOfficeScreenBase<domain::accounting::AccountingControllerPtr>,
                    public domain::accounting::AccountingViewInterface {
 public:
    AccountingScreen();
    ~AccountingScreen() = default;

    // ScreenInterface
    void show(std::promise<defines::display>* promise) override;

 private:
    void showLandingScreen() const;
    void showOptions() const override;
    void queryTransactionsList();
    Options getUserSelection();
    bool action(Options option, std::promise<defines::display>* nextScreen);
    void showSales(domain::accounting::Period period);

    app::utility::TableHelper<entity::Sale> mSalesTable;
    app::utility::TableHelper<DomainGraphMemberWrapper> mTodaysSalesReport;
    app::utility::TableHelper<DomainGraphMemberWrapper> mCategorySalesReport;
    bool isShowingDetailsScreen;

    // Domain interface implementation
    void showInvalidDateTimeRange();
};

// Used for Sales Report tables
class DomainGraphMemberWrapper {
 public:
    explicit DomainGraphMemberWrapper(const domain::accounting::GraphMember& gm)
      : mGraphMember(gm) {}
    inline std::string getKey() const {
        return mGraphMember.key;
    }
    inline std::string getValue() const {
        return mGraphMember.value;
    }
 private:
    domain::accounting::GraphMember mGraphMember;
};

}  // namespace backoffice
}  // namespace screen
#endif  // ORCHESTRA_APPLICATION_SCREEN_BACKOFFICE_ACCOUNTINGSCREEN_HPP_
