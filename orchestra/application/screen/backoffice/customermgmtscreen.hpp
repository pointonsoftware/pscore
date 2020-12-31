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
#include <future>
#include <memory>
#include <string>
#include <vector>
#include <domain/customermgmt/interface/customermgmtviewif.hpp>
#include <screeniface.hpp>
#include <tablehelper.hpp>
// core
#include <domain/customermgmt/interface/customermgmtiface.hpp>
// data
#include <customerdata.hpp>

namespace screen {
namespace backoffice {

class CustomerMgmtScreen : public screen::ScreenInterface,
                           public domain::customermgmt::CustomerManagementViewInterface {
 public:
    CustomerMgmtScreen();
    ~CustomerMgmtScreen() = default;

    // ScreenInterface
    void show(std::promise<defines::display>* promise) override;
    // CoreView implementation
    void showListIsEmptyPopup() override;
    void showDataNotReadyScreen() override;
    void showSuccessfullyRemoved(const std::string& customerName) override;

 private:
    std::unique_ptr<domain::customermgmt::CustomerManagementControlInterface> mCoreController;
    app::utility::TableHelper<entity::Customer> mTableHelper;
    bool isShowingDetailsScreen;
    static const std::vector<std::string> domainFields;
};

}  // namespace backoffice
}  // namespace screen
#endif  // ORCHESTRA_APPLICATION_SCREEN_BACKOFFICE_CUSTOMERMGMTSCREEN_HPP_
