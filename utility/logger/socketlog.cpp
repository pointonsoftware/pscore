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
#include "socketlog.hpp"

// Socket headers
#include <string.h>

#ifdef WIN32
#include <io.h>
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#else
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

#include <iostream>
#include <iomanip>

namespace utility {

constexpr unsigned int PORT = 2020;

void SocketLogger::write(const std::string& logMode, const std::string& className,
                           const std::string& methodName, const std::string& logString) {
    // [2020-08-30 02:46:10.824] | SomeClass | SomeFunc |-- Hello World!
    std::ostringstream stream;
    stream << getLogModeTerminalColor(logMode)
              << getTimestamp() << std::left << " | "
              << std::setw(MAX_CLASS_NAME_SIZE) << className  << " | "
              << std::setw(MAX_FUNC_NAME_SIZE)  << methodName << " |-- "
              << logString << "\033[0m"<< std::endl;

    broadcast(stream.str());
}

void SocketLogger::broadcast(const std::string& logStr) {
    struct sockaddr_in send_addr;
    int fd;
#ifdef WIN32
    char trueflag = '1';
    WSADATA wsaData;

    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != NO_ERROR) {
          return;
    }
#else
    int trueflag = 1;
#endif

    if ((fd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        return;
    }

    if (setsockopt(fd, SOL_SOCKET, SO_BROADCAST,
                   &trueflag, sizeof(trueflag)) < 0) {
        return;
    }

    memset(&send_addr, 0, sizeof(send_addr));
    // Bind the socket to any address and the specified port.
    send_addr.sin_family = AF_INET;
    send_addr.sin_port = htons(PORT);
    send_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

    if (sendto(fd, logStr.c_str(), logStr.size(), 0,
            (struct sockaddr*) &send_addr, sizeof(send_addr)) < 0) {
            close(fd);
            return;
    }

    close(fd);
}

}  // namespace utility
