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

void LogHelper::write(const std::string& logMode, const std::string& prettyFunction, const std::string& logString) const {
    if(isLogModeWritable(logMode)) {
        const std::string methodName = getMethodName(prettyFunction);
        m_logger->write(extractClassName(methodName), extractMethodName(methodName), logString);
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
    const size_t colons = prettyFunction.find("::");
    if((colons < MIN_CHAR) || (colons > MAX_NAME)) {
        return "unknown";
    }
    const size_t begin = prettyFunction.substr(0,colons).rfind(" ") + 1;
    const size_t end = prettyFunction.rfind("(") - begin;
    return prettyFunction.substr(begin,end) + "()";
}

const std::string LogHelper::extractClassName(const std::string& signature) const {
    const size_t colons = signature.find("::");
    if(signature.empty() || (colons < MIN_CHAR) || (colons > MAX_NAME)) {
        return "unknown";
    }
    return signature.substr(0, colons);
}

const std::string LogHelper::extractMethodName(const std::string& signature) const {
    const size_t colons = signature.find("::");
    if(signature.empty() || (colons < MIN_CHAR) || (colons > MAX_NAME)) {
        return "unknown";
    }
    std::string name = signature.substr(colons+2);
    return name.substr(0, name.find("("));;
}   

}  // namespace utility