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
#ifndef CORE_DOMAIN_COMMON_BASECONTROLLER_HPP_
#define CORE_DOMAIN_COMMON_BASECONTROLLER_HPP_
#include <functional>
#include <map>
#include <memory>
#include <string>
#include <utility>
#include <vector>
#include <logger/loghelper.hpp>
#include "cachecontroller.hpp"

namespace domain {

template <typename DpType, typename ViewType, typename EntityType>
class BaseController {
 public:
    explicit BaseController(const std::shared_ptr<DpType> data,
                            const std::shared_ptr<ViewType> view) {
        if ((data == nullptr) || (view == nullptr)) {
           throw std::invalid_argument("Received a nulltpr argument");
        }
        mDataProvider = data;
        mView = view;
    }
    virtual ~BaseController() = default;

 protected:
    /**
     *  Logs the validation results for debugging purposes
     */
    typedef std::map<std::string, std::string> ValidationErrors;
    void dumpValidationResult(const ValidationErrors& errors) const {
      LOG_DEBUG("Dumping validation result");
      for (auto const &result : errors) {
         LOG_DEBUG(std::string(result.first + " -> " + result.second).c_str());
      }
    }

    typedef std::pair<std::string, std::function<std::string(const EntityType&)>> Keys;
    std::shared_ptr<DpType> mDataProvider;
    std::shared_ptr<ViewType> mView;
    CacheController<EntityType> mCachedList;
};

}  // namespace domain

#endif  // CORE_DOMAIN_COMMON_BASECONTROLLER_HPP_