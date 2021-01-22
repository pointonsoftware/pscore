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
#ifndef CORE_DOMAIN_COMMON_CACHECONTROLLER_HPP_
#define CORE_DOMAIN_COMMON_CACHECONTROLLER_HPP_
#include <functional>
#include <string>
#include <vector>

namespace domain {

 /**
 *  Cache list wrapper
 */

template <typename EntityType>
class CacheController {
 public:
    CacheController() = default;
    virtual ~CacheController() = default;

    /**
     *  Sets cached data
     */
    void fill(const std::vector<EntityType>& list) {
        mCachedList = list;
    }

    /**
     *  Returns a copy of cached data
     */
    const std::vector<EntityType>& get() {
        return mCachedList;
    }

    /**
     *  Adds data to the list
     */
    void insert(const EntityType& data) {
        mCachedList.emplace_back(data);
    }

    /**
     *  Removes data to the list
     */
    void erase(const typename std::vector<EntityType>::iterator it) {
        mCachedList.erase(it);
    }

    /**
     *  Checks if cache list is not empty
     */
    bool hasData() {
        return !mCachedList.empty();
    }

    /**
     *  Returns cache size
     */
    size_t dataCount() {
        return mCachedList.size();
    }

    /**
     *  Returns an iterator referring to the past-the-end element in the cache list
     */
    typename std::vector<EntityType>::iterator endOfData() {
        return mCachedList.end();
    }

    /**
     *  Sets the function (ptr) that returns the entity ID
     */
    void setEntityKeyFn(const std::function<std::string(const EntityType&)> entiyKeyFn) {
        mEntiyKeyFn = entiyKeyFn;
    }

    /**
     *  @param [in] - the key or id string that you want to find
     *  Note: This throws a runtime error; Use setEntityKeyFn() prior to calling this function.
     */
    typename std::vector<EntityType>::iterator find(const std::string& key) {
        if (!mEntiyKeyFn) {
            throw std::runtime_error("Entity function key is not usable.");
        }
        return std::find_if(mCachedList.begin(), mCachedList.end(),
                    [this, &key](const EntityType& e) { return mEntiyKeyFn(e) == key; });
    }

    /**
     *  @param [in] - the key or id string that you want to find
     *  Note: This throws a runtime error; Use setEntityKeyFn() prior to calling this function.
     */
    bool isExists(const std::string& key) {
         return find(key) != mCachedList.end();
    }

 private:
    std::vector<EntityType> mCachedList;
    // The function that returns the key ID of the entity
    std::function<std::string(const EntityType&)> mEntiyKeyFn;
};

}  // namespace domain
#endif  // CORE_DOMAIN_COMMON_CACHECONTROLLER_HPP_