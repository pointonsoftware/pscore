/**************************************************************************************************
*                      Copyright (C) Pointon Software - All Rights Reserved                       *
*                                                                                                 *
*             Unauthorized copying of this file via any medium is strictly prohibited             *
*                                  Proprietary and confidential                                   *
*                                                                                                 *
*                   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020                   *
*                                                                                                 *
**************************************************************************************************/
#ifndef UTILITY_INC_LOGGER_LOGHELPER_HPP_
#define UTILITY_INC_LOGGER_LOGHELPER_HPP_

#include "loggeriface.hpp"
#include <memory>
#include <string>

#define LOG_DEBUG(log_str...) utility::LogHelper::GetInstance().write("debug", __PRETTY_FUNCTION__, log_str)
#define LOG_INFO(log_str...)  utility::LogHelper::GetInstance().write("info" , __PRETTY_FUNCTION__, log_str)
#define LOG_WARN(log_str...)  utility::LogHelper::GetInstance().write("warn" , __PRETTY_FUNCTION__, log_str)
#define LOG_ERROR(log_str...) utility::LogHelper::GetInstance().write("error", __PRETTY_FUNCTION__, log_str)

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
#endif  // UTILITY_INC_LOGGER_LOGHELPER_HPP_