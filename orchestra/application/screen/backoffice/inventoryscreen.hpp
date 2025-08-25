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
#include <map>
#include <string>
#include <vector>
// Core
#include <domain/inventory/interface/inventoryviewif.hpp>
#include <domain/inventory/interface/inventoryiface.hpp>
#include <inventorydata.hpp>
// Screens
#include "backofficescreenbase.hpp"
#include <fieldhelper.hpp>
#include <screeniface.hpp>
#include <tablehelper.hpp>

namespace screen {
namespace backoffice {

class InventoryScreen : public screen::ScreenInterface,
                        public BackOfficeScreenBase
                               <domain::inventory::InventoryControllerPtr>,
                        public domain::inventory::InventoryViewInterface {
 public:
    InventoryScreen();
    ~InventoryScreen() override = default;

    // ScreenInterface
    void show(std::promise<defines::display>* promise) override;
    // CoreView implementation
    void showProductsEmptyPopup() override;
    void showDataNotReadyScreen() override;
    void showSuccessfullyRemoved(const std::string& barcode) override;

 private:
    void showLandingScreen() const;
    void queryProductsList();
    void showProducts() const;
    Options getUserSelection();
    bool action(Options option, std::promise<defines::display>* nextScreen);
    void showProductDetails(bool showIndex = false) const;
    const std::string getEntityField(unsigned int index) const;
    void removeProduct();
    void createProduct();
    void updateProduct();
    void handleValidationResults(const std::map<std::string, std::string>& results) const;
    void printValidUOMs() const;
    void printValidCategories() const;

    app::utility::TableHelper<entity::Product> mTableHelper;
    app::utility::FieldHelper<entity::Product> mfieldHelper;
    bool isShowingDetailsScreen;
};

}  // namespace backoffice
}  // namespace screen
#endif  // ORCHESTRA_APPLICATION_SCREEN_BACKOFFICE_INVENTORYSCREEN_HPP_
