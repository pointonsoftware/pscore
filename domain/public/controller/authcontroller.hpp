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
#ifndef DOMAIN_PUBLIC_CONTROLLER_AUTHCONTROLLER_HPP_
#define DOMAIN_PUBLIC_CONTROLLER_AUTHCONTROLLER_HPP_

#include <string>
#include <memory>
#include <defines.hpp>
#include <view/authviewif.hpp>
#include <dataprovider/authdataif.hpp>

namespace domain {
namespace authentication {

class AuthController {
 public:
    explicit AuthController(std::unique_ptr<AuthViewIface>&& view,
                            std::unique_ptr<AuthDataProviderIface>&& dataprovider);
    bool login(const std::string& pin);
 private:
    status::General authenticate(const std::string& pin);
    std::unique_ptr<AuthViewIface> mView;
    std::unique_ptr<AuthDataProviderIface> mDataProvider;
};

}  // namespace authentication
}  // namespace domain
#endif  // DOMAIN_PUBLIC_CONTROLLER_AUTHCONTROLLER_HPP_