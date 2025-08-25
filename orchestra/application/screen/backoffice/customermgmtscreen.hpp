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
#ifndef ORCHESTRA_APPLICATION_SCREEN_BACKOFFICE_CUSTOMERMGMTSCREEN_HPP_
#define ORCHESTRA_APPLICATION_SCREEN_BACKOFFICE_CUSTOMERMGMTSCREEN_HPP_
#include <string>
#include <vector>
// Core
#include <domain/customermgmt/interface/customermgmtiface.hpp>
#include <domain/customermgmt/interface/customermgmtviewif.hpp>
#include <customerdata.hpp>
// Screens
#include "backofficescreenbase.hpp"
#include <fieldhelper.hpp>
#include <screeniface.hpp>
#include <tablehelper.hpp>
#include <informationfieldhelper.hpp>

namespace screen {
namespace backoffice {

class CustomerMgmtScreen : public screen::ScreenInterface,
                           public BackOfficeScreenBase<domain::customermgmt::CustomerMgmtCtrlPtr>,
                           public domain::customermgmt::CustomerManagementViewInterface {
 public:
    CustomerMgmtScreen();
    ~CustomerMgmtScreen() override = default;

    // ScreenInterface
    void show(std::promise<defines::display>* promise) override;
    // CoreView implementation
    void showListIsEmptyPopup() override;
    void showDataNotReadyScreen() override;
    void showSuccessfullyRemoved(const std::string& customerName) override;

 private:
    void showLandingScreen() const;
    void queryCustomersList();
    void showCustomers() const;
    void showCustomerDetails(bool showIndex = false) const;
    void createCustomer();
    void updateCustomer();
    void removeCustomer();
    Options getUserSelection();
    bool action(Options option, std::promise<defines::display>* nextScreen);
    bool fillCustomerInformation(entity::Customer* customer,
                                 const std::vector<std::string>& fields = {});
    app::utility::TableHelper<entity::Customer> mTableHelper;
    app::utility::FieldHelper<entity::Customer> mCustomerFieldHelper;
    app::utility::InformationFieldHelper mOtherInfoFieldHelper;
    bool isShowingDetailsScreen;
};

}  // namespace backoffice
}  // namespace screen
#endif  // ORCHESTRA_APPLICATION_SCREEN_BACKOFFICE_CUSTOMERMGMTSCREEN_HPP_
