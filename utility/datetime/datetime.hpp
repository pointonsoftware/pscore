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
#ifndef UTILITY_DATETIME_DATETIME_HPP_
#define UTILITY_DATETIME_DATETIME_HPP_
#include <chrono>
#include <string>

namespace utility {

// Represents the start and end dates of a week
struct WeekEndDates {
    const std::string start;
    const std::string end;
};

/*!
 * Returns the current date-time
*/
extern std::tm currentDateTime();
/*!
 * Returns the current date-time in "YYYY-MM-DD HH:MM:SS" form
*/
extern std::string currentDateTimeStr();
/*!
 * Returns the current date in "YYYY-MM-DD" form
*/
extern std::string currentDateStr();
/*!
 * Returns the current day's number of month
 * e.g. 2020-10-12 returns 12
*/
extern unsigned int currentDayOfTheMonth();
/*!
 * Returns the number of days in the current month
*/
extern int daysOfCurrentMonth();
/*!
 * Returns the yesterday date in "YYYY-MM-DD" form
*/
extern std::string yesterdayDateStr();
/*!
 * Returns the current month in "MM" form
*/
extern std::string currentMonthStr();
/*!
 * Returns the current year in "YYYY" form
*/
extern std::string currentYearStr();
/*!
 * Validate if date is in "YYYY-MM-DD" form
*/
extern bool isValidDate(const std::string& date);
/*!
 * Validate if date-time is in "YYYY-MM-DD HH:MM:SS" form
*/
extern bool isValidDateTime(const std::string& dateTime);
/*!
 * Returns the current week's start and end dates in "YYYY-MM-DD" form
*/
extern WeekEndDates currentWeekEndDates();

class DateTimeComparator {
 public:
    DateTimeComparator() = default;
    ~DateTimeComparator() = default;

    enum class Result : int8_t {
        INVALID_DATE = -2,
        LESSER_THAN = -1,
        EQUALS = 0,
        GREATER_THAN = 1
    };

    inline DateTimeComparator& operator()(const std::string& date) {
        mDate = date;
        return *this;
    }
    /*!
    * Compares member date to argument date.
    * e.g if mDate < date ? return Result::LESSER_THAN;
    */
    Result compare(const std::string& date) const;

 private:
    std::string mDate;
};

}  // namespace utility
#endif  // UTILITY_DATETIME_DATETIME_HPP_
