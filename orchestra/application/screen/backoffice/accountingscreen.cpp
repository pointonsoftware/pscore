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

AccountingScreen::AccountingScreen() : mTableHelper({"ID", "Sale Date", "Grand Total"},
            { &entity::Sale::ID, &entity::Sale::dateTime, &entity::Sale::total }),
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
    mTableHelper.printTable();
    SCREENCOMMON().printHorizontalBorder(defines::BORDER_CHARACTER_2);
}

void AccountingScreen::queryTransactionsList() {
    // @todo - just using test dates to show all sales
    const std::string startDate = "2020/01/01 12:00:00";
    const std::string endDate = "2022/01/01 12:00:00";
    mTableHelper.setData(mCoreController->getCustomPeriodSales(startDate, endDate));
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

}  // namespace backoffice
}  // namespace screen
