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
#ifndef UTILITY_LOGGER_LOGHELPER_HPP_
#define UTILITY_LOGGER_LOGHELPER_HPP_

#include <memory>
#include <string>
#include "loggeriface.hpp"

#define FUNC __PRETTY_FUNCTION__
#define LOG_DEBUG(log_str...) utility::LogHelper::GetInstance().write("debug", FUNC, log_str)
#define LOG_INFO(log_str...)  utility::LogHelper::GetInstance().write("info" , FUNC, log_str)
#define LOG_WARN(log_str...)  utility::LogHelper::GetInstance().write("warn" , FUNC, log_str)
#define LOG_ERROR(log_str...) utility::LogHelper::GetInstance().write("error", FUNC, log_str)

namespace utility {

class LogHelper {
 public:
    static LogHelper& GetInstance() {
        static LogHelper loghelper;
        return loghelper;
    }
    void write(const std::string& logMode, const std::string& prettyFunction,
               const std::string& logFormat...) const;

 private:
    LogHelper();
    const bool isLogModeWritable(const std::string& logMode) const;
    const std::string getMethodName(const std::string& prettyFunction) const;
    const std::string extractClassName(const std::string& signature) const;
    const std::string extractMethodName(const std::string& signature) const;

    std::unique_ptr<LoggerInterface> m_logger;

    enum class LoggerType {
        CONSOLE = 0x00,
        FILE    = 0x01,
        SOCKET  = 0x02
    };

    enum class LogLevel {
        VERBOSE   = 0x01,
        NORMAL    = 0x02,
        ALERT     = 0x03,
        CRITICAL  = 0x04
    } m_logLevel;
};

}  // namespace utility
#endif  // UTILITY_LOGGER_LOGHELPER_HPP_