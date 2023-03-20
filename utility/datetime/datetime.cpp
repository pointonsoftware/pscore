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

constexpr unsigned int MAX_CHAR_LENGTH = 100;
constexpr uint8_t END_OF_WEEK_DAY_INDEX = 6;

// Developer note: How To's for date.h
// https://github.com/HowardHinnant/date/wiki/Examples-and-Recipes

bool isValidDate(const std::string& date) {
    std::istringstream date_ss(date);
    date::year_month_day ymd;
    date_ss >> date::parse("%Y-%m-%d", ymd);
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
#elif WIN32
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
    char buff[MAX_CHAR_LENGTH];
    snprintf(buff, sizeof(buff), "%04u-%02u-%02u %02u:%02u:%02u", bt.tm_year + 1900,
             bt.tm_mon + 1, bt.tm_mday, bt.tm_hour, bt.tm_min, bt.tm_sec);
    return buff;
}

std::string currentDateStr() {
    const std::tm& bt = currentDateTime();
    char buff[MAX_CHAR_LENGTH];
    snprintf(buff, sizeof(buff), "%04u-%02u-%02u", bt.tm_year + 1900, bt.tm_mon + 1, bt.tm_mday);
    return buff;
}

std::string currentMonthStr() {
    date::year_month_day ymd = date::floor<date::days>(std::chrono::system_clock::now());
    char buff[MAX_CHAR_LENGTH];
    snprintf(buff, sizeof(buff), "%02u", static_cast<unsigned>(ymd.month()));
    return buff;
}

unsigned int currentDayOfTheMonth() {
    date::year_month_day ymd = date::floor<date::days>(std::chrono::system_clock::now());
    return static_cast<unsigned>(ymd.day());
}

int daysOfCurrentMonth() {
    date::year_month_day ymd = date::floor<date::days>(std::chrono::system_clock::now());
    date::days days = (ymd.year()/ymd.month()/date::last).day() - date::day{0};
    return days.count();
}

std::string yesterdayDateStr() {
    std::tm bt = currentDateTime();
    bt.tm_mday -= 1;  // substract one day
    std::mktime(&bt);  // normalize
    char buff[MAX_CHAR_LENGTH];
    snprintf(buff, sizeof(buff), "%04u-%02u-%02u", bt.tm_year + 1900, bt.tm_mon + 1, bt.tm_mday);
    return buff;
}

std::string currentYearStr() {
    date::year_month_day ymd = date::floor<date::days>(std::chrono::system_clock::now());
    char buff[MAX_CHAR_LENGTH];
    snprintf(buff, sizeof(buff), "%d", static_cast<int>(ymd.year()));
    return std::string(buff);
}

WeekEndDates currentWeekEndDates() {
    const std::tm& bt = currentDateTime();
    std::tm startDate = bt;
    std::tm endDate = bt;
    // day of the week - [0, 6] representing [Sunday, Saturday]
    const int dayOfTheWeek = bt.tm_wday;
    // Calculate the start and end dates
    // e.g. weekday = 4
    // start date  = currentdate() - weekday
    // end date = currentdate() + 6 - weekday
    startDate.tm_mday = startDate.tm_mday - dayOfTheWeek;
    endDate.tm_mday = endDate.tm_mday + END_OF_WEEK_DAY_INDEX - dayOfTheWeek;
    // normalize
    std::mktime(&startDate);
    std::mktime(&endDate);
    // format
    char sDate[MAX_CHAR_LENGTH];
    snprintf(sDate, sizeof(sDate), "%04u-%02u-%02u", startDate.tm_year + 1900,
         startDate.tm_mon + 1, startDate.tm_mday);
    char eDate[MAX_CHAR_LENGTH];
    snprintf(eDate, sizeof(eDate), "%04u-%02u-%02u", endDate.tm_year + 1900,
         endDate.tm_mon + 1, endDate.tm_mday);
    return {sDate, eDate};
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
            return "%Y-%m-%d";
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
