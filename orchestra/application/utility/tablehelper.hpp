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
#ifndef ORCHESTRA_APPLICATION_UTILITY_TABLEHELPER_HPP_
#define ORCHESTRA_APPLICATION_UTILITY_TABLEHELPER_HPP_
#include <functional>
#include <string>
#include <vector>
#include "screencommon.hpp"

namespace app {
namespace utility {

template <typename T>
class TableHelper {
 public:
    explicit TableHelper(const std::vector<std::string>& columns,
                         const std::vector<std::function<std::string(const T&)>>& columnData)
        : mCurrentIndex(0), mColumns(columns), mColumnData(columnData) {}
    TableHelper() = delete;

    inline void setData(const std::vector<T>& data) {
        mTableList = data;
    }

    inline T getData(const uint8_t index) const {
        return mTableList[index];
    }

    inline void deleteData(const uint8_t index) {
        mTableList.erase(mTableList.begin() + index);
    }

    inline void setCurrentIndex(const uint8_t index) {
        mCurrentIndex = index;
    }

    inline uint8_t getCurrentIndex() const {
        return mCurrentIndex;
    }

    inline uint8_t getDataCount() const {
        return mTableList.size();
    }

    inline void printTable() const {
        SCREENCOMMON().printColumns(mColumns, true);
        for (unsigned int index = 0; index < mTableList.size(); ++index) {
            SCREENCOMMON().printColumns({std::string("[" + std::to_string(index + 1) + "] "
                                        + mColumnData[0](mTableList[index])),
                                          mColumnData[1](mTableList[index]),
                                          mColumnData[2](mTableList[index]),
                                          mColumnData[3](mTableList[index])});
        }
    }

 private:
    std::vector<T> mTableList;  // Represents the GUI table
    uint8_t mCurrentIndex;  // 1-based index
    const std::vector<std::string> mColumns;
    const std::vector<std::function<std::string(const T&)>> mColumnData;
};

}  // namespace utility
}  // namespace app
#endif  // ORCHESTRA_APPLICATION_UTILITY_TABLEHELPER_HPP_