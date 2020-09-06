/**************************************************************************************************
*                      Copyright (C) Pointon Software - All Rights Reserved                       *
*                                                                                                 *
*             Unauthorized copying of this file via any medium is strictly prohibited             *
*                                  Proprietary and confidential                                   *
*                                                                                                 *
*                   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020                   *
*                                                                                                 *
**************************************************************************************************/
#ifndef UTILITY_INC_LOGGER_FILELOG_HPP_
#define UTILITY_INC_LOGGER_FILELOG_HPP_

#include <string>
#include "loggeriface.hpp"

namespace utility {

class FileLogger : public LoggerInterface {
 private:
    void write(const std::string& logMode, const std::string& className,
               const std::string& methodName, const std::string& logString) override;
};

}  // namespace utility
#endif  // UTILITY_INC_LOGGER_FILELOG_HPP_