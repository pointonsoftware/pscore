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
#ifndef CORE_DOMAIN_SALES_INTERFACE_SALESIFACE_HPP_
#define CORE_DOMAIN_SALES_INTERFACE_SALESIFACE_HPP_
#include <memory>
#include "salesdataif.hpp"
#include "salesviewif.hpp"
#include <domain/common/librarycommon.hpp>

namespace domain {
namespace sales {

class SalesControlInterface {
 public:
    SalesControlInterface() = default;
    virtual ~SalesControlInterface() = default;
};

typedef std::shared_ptr<SalesDataInterface> SalesDataPtr;
typedef std::shared_ptr<SalesViewInterface> SalesViewPtr;
typedef std::unique_ptr<SalesControlInterface> SalesControllerPtr;

// Lib APIs
extern "C" CORE_API SalesControllerPtr createSalesModule
                    (const SalesDataPtr& data, const SalesViewPtr& view);

}  // namespace sales
}  // namespace domain
#endif  // CORE_DOMAIN_SALES_INTERFACE_SALESIFACE_HPP_