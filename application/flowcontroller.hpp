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
#ifndef APPLICATION_PRESENTER_FLOWCONTROLLER_HPP_
#define APPLICATION_PRESENTER_FLOWCONTROLLER_HPP_

namespace view {

#define FLOWCONTROLLER() FlowController::getInstance()

class FlowController {
 public:
    ~FlowController() = default;

    static FlowController& getInstance() {
        static FlowController instance;
        return instance;
    }

    /*!
     * Main execution
    */
    void run();

 private:
    FlowController() = default;
    void showLoginScreen();
};

}  // namespace view
#endif  // APPLICATION_PRESENTER_FLOWCONTROLLER_HPP_