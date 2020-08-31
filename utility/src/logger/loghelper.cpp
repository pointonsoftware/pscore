/**************************************************************************************************
*                      Copyright (C) Pointon Software - All Rights Reserved                       *
*                                                                                                 *
*             Unauthorized copying of this file via any medium is strictly prohibited             *
*                                  Proprietary and confidential                                   *
*                                                                                                 *
*                   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020                   *
*                                                                                                 *
**************************************************************************************************/
#include "logger/loghelper.hpp"
#include "logger/consolelog.hpp"
#include "logger/filelog.hpp"
#include "logger/socketlog.hpp"
#include <cstdarg>
#include <string>
#include <vector>

/**
* This code is sourced from StackOverflow
* Author profile: https://stackoverflow.com/users/3990012/serup
*
* Original question: https://stackoverflow.com/q/15106102
* Answer: https://stackoverflow.com/a/52184144
*/
#define EXTRACT_VAR(logFormat, logString) \
    do { \
        va_list args; \
        va_start(args, logFormat); \
        const size_t len = std::vsnprintf(NULL, 0, logFormat.c_str(), args); \
        va_end(args); \
        std::vector<char> vec(len + 1); \
        va_start(args, logFormat); \
        std::vsnprintf(&vec[0], len + 1, logFormat.c_str(), args); \
        va_end(args); \
        logString = &vec[0]; \
    } while (0)

namespace utility {

LogHelper::LogHelper() {
    // read from config

    // m_logger = config->What is the logger type? (getConfig(logger) == LoggerType::?)
    // We default to console for now.
    m_logger = std::make_unique<ConsoleLogger>();

    // m_logLevel = config -> What is the log level?
    // We default to Verbose for now.
    m_logLevel = LogLevel::VERBOSE;
}

void LogHelper::write(const std::string& logMode, const std::string& prettyFunction,
                      const std::string& logFormat...) const {
    if(isLogModeWritable(logMode)) {
        const std::string signature = getMethodName(prettyFunction);
        const std::string className = extractClassName(signature);
        const std::string methodName = extractMethodName(signature);
        std::string logString = logFormat;
        //! logFormat might have arguments
        if (logFormat.find("%") != std::string::npos) {
            EXTRACT_VAR(logFormat, logString);
        }
        m_logger->write(className, methodName, logString);
    }
}

const bool LogHelper::isLogModeWritable(const std::string& logMode) const {
    if(logMode.compare("debug") == 0) {
        return m_logLevel == LogLevel::VERBOSE;
    }
    if(logMode.compare("info") == 0) {
        return (m_logLevel == LogLevel::VERBOSE) ||
               (m_logLevel == LogLevel::NORMAL);
    }
    if(logMode.compare("warn") == 0) {
        return m_logLevel != LogLevel::CRITICAL;
    }
    return true;
}

const std::string LogHelper::getMethodName(const std::string& prettyFunction) const {
    size_t colons = prettyFunction.find("::");
    if((colons < MIN_CHAR) || (colons > MAX_NAME)) {
        colons = MAX_NAME;
    }
    const size_t begin = prettyFunction.substr(0,colons).rfind(" ") + 1;
    const size_t end = prettyFunction.rfind("(") - begin;
    return prettyFunction.substr(begin,end);
}

const std::string LogHelper::extractClassName(const std::string& signature) const {
    const size_t colons = signature.find("::");
    if(signature.empty() || (colons < MIN_CHAR) || (colons > MAX_NAME)) {
        return "unknown";
    }
    return signature.substr(0, colons);
}

const std::string LogHelper::extractMethodName(const std::string& signature) const {
    if(signature.empty()) {
        return "unknown";
    }
    const size_t colons = signature.find("::");
    const size_t begin = [&colons]{
        return (colons < MIN_CHAR) || (colons > MAX_NAME) ? 0 : colons + 2;
    }();
    return signature.substr(begin);
}

}  // namespace utility