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
#include "accountingscreen.hpp"
#include <algorithm>
#include <memory>
#include <accountingdata.hpp>
#include <logger/loghelper.hpp>

namespace screen {
namespace backoffice {

// Product fields
const std::vector<std::string> DOMAIN_FIELDS {
    "Sale.ID",
    "Sale.Timestamp",
    "Sale.Items",
    "Sale.Subtotal",
    "Sale.Tax",
    "Sale.Discount",
    "Sale.Total",
    "Sale.Paid",
    "Sale.Payment.Type",
    "Sale.Change",
    "Sale.CashierID",
    "Sale.CustomerID"
};

AccountingScreen::AccountingScreen()
            : mSalesTable({"ID", "Sale Date", "Grand Total"},
            { &entity::Sale::ID, &entity::Sale::dateTime, &entity::Sale::total }),
            mTodaysSalesReport({"Hour", "Total Sale"},
            { &DomainGraphMemberWrapper::getKey, &DomainGraphMemberWrapper::getValue }),
            isShowingDetailsScreen(false) {
    // Empty for now
}

void AccountingScreen::show(std::promise<defines::display>* promise) {
    mCoreController = domain::accounting::createAccountingModule(
                    std::make_shared<dataprovider::accounting::AccountingDataProvider>(),
                    std::make_shared<AccountingScreen>());
    // Get the customers from Core then cache the list
    queryTransactionsList();
    // Landing
    showLandingScreen();
    do {} while (action(getUserSelection(), promise));
}

void AccountingScreen::showLandingScreen() const {
    LOG_DEBUG("Showing accounting information screen");
    SCREENCOMMON().showTopBanner("Accounting Information");
    // @todo - show data according to Product Requirement / Screen Design
    std::cout << std::endl;
    std::cout << "Total transactions count: " << mSalesTable.getDataCount() << std::endl;
    mSalesTable.printTable();
    std::cout << std::endl;
    SCREENCOMMON().printTitleText("Hourly Sales Table", false);
    mTodaysSalesReport.printTable();
    showOptions();
}

void AccountingScreen::queryTransactionsList() {
    LOG_DEBUG("Sending transaction list request to accounting domain");
    // @todo - just using test dates to show all sales
    const std::string startDate = "2020/05/10 09:00:00";
    const std::string endDate = "2022/05/10 12:00:00";
    mSalesTable.setData(mCoreController->getCustomPeriodSales(startDate, endDate));
    // Convert core data into table-readable type
    const domain::accounting::GraphReport& coreReport =  mCoreController->getTodaySalesReport();
    std::vector<DomainGraphMemberWrapper> report;
    for (domain::accounting::GraphMember member : coreReport) {
        report.emplace_back(member);
    }
    mTodaysSalesReport.setData(report);
}

AccountingScreen::Options AccountingScreen::getUserSelection() {
    std::string userInput;
    std::cout << std::endl << "Select [option] > "; std::cin >> userInput;

    if (userInput == "x") {
        return Options::APP_EXIT;
    } else if (userInput == "b") {
         // We should return whatever was the previous screen
        // For now, we will check if the info screen is shown
        return isShowingDetailsScreen ? Options::LANDING : Options::DASHBOARD;
    } else if (userInput == "0") {
        return Options::LOGOUT;
    }  // add more options here

    // Default invalid option
    return Options::INVALID;
}

bool AccountingScreen::action(Options option, std::promise<defines::display>* nextScreen) {
    bool switchScreenIsRequired = false;
    switch (option) {
        case Options::DASHBOARD:
            switchScreenIsRequired = true;
            nextScreen->set_value(defines::display::DASHBOARD);
            break;
        case Options::LOGOUT:
            switchScreenIsRequired = true;
            nextScreen->set_value(defines::display::LOGIN);
            break;
        case Options::INVALID:
            invalidOptionSelected();
            break;
        case Options::APP_EXIT:  // Fall-through
        default:
            switchScreenIsRequired = true;
            nextScreen->set_value(defines::display::EXIT);
            break;
    }
    // Return "false" if switch screen is required so we proceed to the next screen
    return !switchScreenIsRequired;
}

void AccountingScreen::showInvalidDateTimeRange() {
    LOG_DEBUG("Showing invalid date-time screen");
    std::cout << "Invalid date-time range!" << std::endl;
    // Let the user confirm
    std::cin.ignore();
    std::cin.get();
}

}  // namespace backoffice
}  // namespace screen
