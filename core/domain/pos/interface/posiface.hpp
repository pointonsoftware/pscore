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
#ifndef CORE_DOMAIN_POS_INTERFACE_POSIFACE_HPP_
#define CORE_DOMAIN_POS_INTERFACE_POSIFACE_HPP_
#include <memory>
#include "posdataif.hpp"
#include "posviewif.hpp"
#include <domain/common/librarycommon.hpp>

namespace domain {
namespace pos {

class POSControlInterface {
 public:
    POSControlInterface() = default;
    virtual ~POSControlInterface() = default;
};

typedef std::shared_ptr<POSDataInterface> POSDataPtr;
typedef std::shared_ptr<POSViewInterface> POSViewPtr;
typedef std::unique_ptr<POSControlInterface> POSControllerPtr;

// Lib APIs
CORE_API POSControllerPtr createPOSModule
(const POSDataPtr& data, const POSViewPtr& view);

}  // namespace pos
}  // namespace domain
#endif  // CORE_DOMAIN_POS_INTERFACE_POSIFACE_HPP_