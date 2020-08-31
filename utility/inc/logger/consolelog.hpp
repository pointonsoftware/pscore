/**************************************************************************************************
*                      Copyright (C) Pointon Software - All Rights Reserved                       *
*                                                                                                 *
*             Unauthorized copying of this file via any medium is strictly prohibited             *
*                                  Proprietary and confidential                                   *
*                                                                                                 *
*                   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020                   *
*                                                                                                 *
**************************************************************************************************/
#ifndef UTILITY_INC_LOGGER_CONSOLELOG_HPP_
#define UTILITY_INC_LOGGER_CONSOLELOG_HPP_

#include "loggeriface.hpp"
#include <string>

namespace utility {

class ConsoleLogger : public LoggerInterface {
 private:
    void write(const std::string& className, const std::string& methodName,
               const std::string& logString) override;
};

}  // namespace utility
#endif  // UTILITY_INC_LOGGER_CONSOLELOG_HPP_