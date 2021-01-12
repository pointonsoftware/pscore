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
#include <map>
#include <memory>
#include <string>
#include <vector>
#include <logger/loghelper.hpp>

namespace domain {

typedef std::map<std::string, std::string> ValidationErrors;

template <typename DpType, typename ViewType, typename EntityType>
class BaseController {
 public:
    BaseController() = default;
    virtual ~BaseController() = default;

 protected:
    void dumpValidationResult(const ValidationErrors& errors) const {
      LOG_DEBUG("Dumping validation result");
      for (auto const &result : errors) {
         LOG_DEBUG(std::string(result.first + " -> " + result.second).c_str());
      }
    }

    std::shared_ptr<DpType> mDataProvider;
    std::shared_ptr<ViewType> mView;

 private:
    std::vector<EntityType> mCachedList;
    bool isExists(const std::string& barcode);
    typename std::vector<EntityType>::iterator find(const std::string& barcode);
};

}  // namespace domain

#endif  // CORE_DOMAIN_COMMON_BASECONTROLLER_HPP_