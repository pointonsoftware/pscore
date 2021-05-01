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
#include "datetime.hpp"
#include <iomanip>
#include <sstream>

namespace utility {
/**
 * Code based-from StackOverflow by alain
 * Author profile: https://stackoverflow.com/users/3435400/alain
 *
 * Original question: https://stackoverflow.com/q/39447921/3975468
 * Answer: https://stackoverflow.com/a/39452595/3975468
*/
bool isValidDate(const std::string& date) {
    std::istringstream date_s(date);
    struct tm date_c, date_c_cmp;
    date_s >> std::get_time(&date_c, "%Y/%m/%d");
    date_c_cmp = date_c;  // store original  to compare later
    std::time_t when = std::mktime(&date_c);  // normalize
    {
#ifdef __unix__
        std::tm bt {};
        localtime_r(&when, &bt);
#elif __WIN32__
        std::tm bt {};
        localtime_s(&bt, &when);
#else
        static std::mutex mtx;
        std::lock_guard<std::mutex> lock(mtx);
        std::localtime(&when);
#endif
    }
    // Compare with original
    if (date_c.tm_year != date_c_cmp.tm_year
        || date_c.tm_mon != date_c_cmp.tm_mon
        || date_c.tm_mday != date_c_cmp.tm_mday) {
        return false;
    }
    return true;
}

bool isValidDateTime(const std::string& dateTime) {
    std::istringstream date_s(dateTime);
    struct tm date_c, date_c_cmp;
    date_s >> std::get_time(&date_c, "%Y/%m/%d %H:%M:%S");
    date_c_cmp = date_c;  // store original  to compare later
    std::time_t when = std::mktime(&date_c);  // normalize
    {
#ifdef __unix__
        std::tm bt {};
        localtime_r(&when, &bt);
#elif __WIN32__
        std::tm bt {};
        localtime_s(&bt, &when);
#else
        static std::mutex mtx;
        std::lock_guard<std::mutex> lock(mtx);
        std::localtime(&when);
#endif
    }
    // Compare with original
    if (date_c.tm_year != date_c_cmp.tm_year
        || date_c.tm_mon != date_c_cmp.tm_mon
        || date_c.tm_mday != date_c_cmp.tm_mday
        || date_c.tm_hour != date_c_cmp.tm_hour
        || date_c.tm_min != date_c_cmp.tm_min
        || date_c.tm_sec != date_c_cmp.tm_sec) {
        return false;
    }
    return true;
}

DateTimeComparator::Result DateTimeComparator::compare(const std::string& date) const {
    if (!isValidDate(mDate) || !isValidDate(date)) {
        return Result::INVALID_DATE;
    }
    std::istringstream date_s(mDate);
    struct tm date_c;
    date_s >> std::get_time(&date_c, "%Y/%m/%d %H:%M:%S");
    std::time_t seconds1 = std::mktime(& date_c);

    std::istringstream date_s2(date);
    struct tm date_c2;
    date_s2 >> std::get_time(&date_c2, "%Y/%m/%d %H:%M:%S");
    std::time_t seconds2 = std::mktime(& date_c2);

    if (seconds1 > seconds2) {
        return Result::GREATER_THAN;
    } else if (seconds1 < seconds2) {
        return Result::LESSER_THAN;
    } else {
        return Result::EQUALS;
    }
}

}  // namespace utility
