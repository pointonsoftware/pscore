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
#ifndef ORCHESTRA_APPLICATION_SCREEN_BACKOFFICE_INVENTORYSCREEN_HPP_
#define ORCHESTRA_APPLICATION_SCREEN_BACKOFFICE_INVENTORYSCREEN_HPP_
#include <future>
#include <memory>
#include <string>
#include <vector>
#include <domain/inventory/interface/inventoryviewif.hpp>
#include <screeniface.hpp>
#include <tablehelper.hpp>
// Core
#include <domain/inventory/interface/inventoryiface.hpp>
// Data
#include <inventorydata.hpp>

namespace screen {
namespace backoffice {

class InventoryScreen : public screen::ScreenInterface,
                        public domain::inventory::InventoryViewInterface {
 public:
    InventoryScreen();
    ~InventoryScreen() = default;

    // ScreenInterface
    void show(std::promise<defines::display>* promise) override;
    // CoreView implementation
    void showProductsEmptyPopup() override;
    void showDataNotReadyScreen() override;
    void showSuccessfullyRemoved(const std::string& barcode) override;

 private:
      // Screen options - this represents the buttons in a GUI
    enum class Options {
        LANDING,
        DASHBOARD,
        PRODUCT_DETAILS,
        PRODUCT_REMOVE,
        PRODUCT_CREATE,
        // add more enums here
        LOGOUT,
        APP_EXIT,
        INVALID
        // Warning! Don't add anything here.
        // New enum values must be added before LOGOUT
    };
    void showLandingScreen() const;
    void queryProductsList();
    void showProducts() const;
    void showOptions() const;
    Options getUserSelection();
    bool action(Options option, std::promise<defines::display>* nextScreen);
    void invalidOptionSelected() const;
    void showProductDetails(bool showIndex = false) const;
    const std::string getEntityField(unsigned int index) const;
    void removeProduct();
    void createProduct();
    void fillProductInformation(entity::Product* product,
                                const std::vector<std::string>& requiredFields) const;

    std::unique_ptr<domain::inventory::InventoryControlInterface> mInventoryController;
    app::utility::TableHelper<entity::Product> mTableHelper;
};

}  // namespace backoffice
}  // namespace screen
#endif  // ORCHESTRA_APPLICATION_SCREEN_BACKOFFICE_INVENTORYSCREEN_HPP_
