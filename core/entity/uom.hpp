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
#ifndef CORE_ENTITY_UOM_HPP_
#define CORE_ENTITY_UOM_HPP_

#include <string>

namespace entity {

class UnitOfMeasurement {
 public:
    UnitOfMeasurement() = default;
    ~UnitOfMeasurement() = default;
    UnitOfMeasurement(const std::string& id, const std::string& name,
                      const std::string& abbreviation)
                     : mID(id), mName(name), mAbbreviation(abbreviation) {}

    std::string ID() const {
        return mID;
    }
    std::string name() const {
        return mName;
    }
    std::string abbreviation() const {
        return mAbbreviation;
    }

 private:
    std::string mID;
    std::string mName;
    std::string mAbbreviation;
};

}  // namespace entity
#endif  // CORE_ENTITY_UOM_HPP_