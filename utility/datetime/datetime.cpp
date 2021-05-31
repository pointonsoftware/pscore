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
#include <date/date.h>
#include <iomanip>
#include <sstream>

namespace utility {

// Developer note: How To's for date.h
// https://github.com/HowardHinnant/date/wiki/Examples-and-Recipes

bool isValidDate(const std::string& date) {
    std::istringstream date_ss(date);
    date::year_month_day ymd;
    date_ss >> date::parse("%Y/%m/%d", ymd);
    return !date_ss.fail();
}

bool isValidDateTime(const std::string& dateTime) {
    std::istringstream date_ss(dateTime);
    date::sys_time<std::chrono::milliseconds> tp;
    date_ss >> date::parse("%Y-%m-%d %H:%M:%S", tp);
    return !date_ss.fail();
}

/**
 * Code based-from StackOverflow by Galik
 * Author profile: https://stackoverflow.com/users/3807729/galik
 *
 * Original question: https://stackoverflow.com/q/38034033/3975468
 * Answer: https://stackoverflow.com/a/38034148/3975468
*/
std::tm currentDateTime() {
    typedef std::chrono::system_clock Clock;
    auto now = Clock::now();
    std::time_t now_c = Clock::to_time_t(now);
    std::tm bt {};
#ifdef __unix__
    localtime_r(&now_c, &bt);
#elif __WIN32__
    localtime_s(&bt, &now_c);
#else
    static std::mutex mtx;
    std::lock_guard<std::mutex> lock(mtx);
    bt = *std::localtime(&now_c);
#endif
    return bt;
}

std::string currentDateTimeStr() {
    const std::tm& bt = currentDateTime();
    char buff[100];
    snprintf(buff, sizeof(buff), "%04u-%02u-%02u %02u:%02u:%02u", bt.tm_year + 1900,
             bt.tm_mon + 1, bt.tm_mday, bt.tm_hour, bt.tm_min, bt.tm_sec);
    return std::string(buff);
}

std::string currentDateStr() {
    const std::tm& bt = currentDateTime();
    char buff[100];
    snprintf(buff, sizeof(buff), "%04u-%02u-%02u", bt.tm_year + 1900, bt.tm_mon + 1, bt.tm_mday);
    return std::string(buff);
}

DateTimeComparator::Result DateTimeComparator::compare(const std::string& date) const {
    const std::string format = [this, date]() {
        // This check sequence should not be changed
        // i.e. check for dateTime first before check date because a dateTime is also a valid date
        //      hence, we will never reach isValidDateTime if we check for valid date first
        if (isValidDateTime(mDate) && isValidDateTime(date)) {
            return "%Y-%m-%d %H:%M:%S";
        }
        if (isValidDate(mDate) && isValidDate(date)) {
            return "%Y/%m/%d";
        }
        return "";  // Empty format means one or both of the strings are invalid date/s
    }();

    if (format.empty()) {
        return Result::INVALID_DATE;
    }

    // Convert the dates to seconds so they can be compared
    std::istringstream date1(mDate);
    struct tm date1TM;
    date1 >> std::get_time(&date1TM, static_cast<const char*>(format.c_str()));
    std::time_t seconds1 = std::mktime(&date1TM);

    std::istringstream date2(date);
    struct tm date2TM;
    date2 >> std::get_time(&date2TM, static_cast<const char*>(format.c_str()));
    std::time_t seconds2 = std::mktime(&date2TM);

    if (seconds1 > seconds2) {
        return Result::GREATER_THAN;
    } else if (seconds1 < seconds2) {
        return Result::LESSER_THAN;
    } else {
        return Result::EQUALS;
    }
}

}  // namespace utility
