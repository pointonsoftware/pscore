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
// Socket headers
#include <unistd.h>
#include <string.h>

#ifdef __WIN32__
#include <winsock2.h>
#pragma comment(lib, "Ws2_32.lib")
#ifndef ENABLE_VIRTUAL_TERMINAL_PROCESSING
#define ENABLE_VIRTUAL_TERMINAL_PROCESSING 0x0004
#endif
#define DEFINE_CONSOLEV2_PROPERTIES
#else
#include <sys/socket.h>
#include <arpa/inet.h>
#endif

#include <iostream>

/*!
 * Compiling with mingw
 * x86_64-w64-mingw32-g++ -o log_client_app.exe logclient.cpp -lws2_32 -static-libgcc
 *      -static-libstdc++ -lstdc++ --static
 * 
*/

constexpr unsigned int PORT = 2020;

void screenStartUp() {
    std::cout << "+------------------------------------------+" << std::endl;
    std::cout << "|          PSCORE Log Client v1.0          |" << std::endl;
    std::cout << "|           (c) Pointon Software           |" << std::endl;
    std::cout << "+------------------------------------------+" << std::endl;
    std::cout << "|   Note: For LAN, enable UDP port 2020    |" << std::endl;
    std::cout << "+------------------------------------------+" << std::endl;
    std::cout << std::endl;
}

void closeSocket(const int& fd) {
#ifdef __WIN32__
    closesocket(fd);
    WSACleanup();
#else
    close(fd);
#endif
    std::cout << "Socket closed" << std::endl;
}

#ifdef _WIN32
// https://docs.microsoft.com/en-us/windows/console/console-virtual-terminal-sequences
bool EnableVTMode() {
    // Set output mode to handle virtual terminal sequences
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut == INVALID_HANDLE_VALUE) {
        std::cout << "VT processing: INVALID_HANDLE_VALUE." << std::endl;
        return false;
    }

    DWORD dwMode = 0;
    if (!GetConsoleMode(hOut, &dwMode)) {
        std::cout << "VT processing: GetConsoleMode failed." << std::endl;
        return false;
    }

    dwMode |= ENABLE_VIRTUAL_TERMINAL_PROCESSING;
    if (!SetConsoleMode(hOut, dwMode)) {
        std::cout << "VT processing: SetConsoleMode failed." << std::endl;
        return false;
    }
    return true;
}
#endif

int main(int argc, char* argv[]) {
    struct sockaddr_in recv_addr;
    int socketfd;
#ifdef __WIN32__
    char trueflag = '1';
    int slen = sizeof(recv_addr);
#else
    int trueflag = 1;
    socklen_t slen = sizeof(recv_addr);
#endif

    screenStartUp();
    std::cout << "Client starting up..." << std::endl;
    std::cout << std::endl;

#ifdef __WIN32__
    WSADATA wsaData;
    int res = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (res != NO_ERROR) {
        std::cout << "WSAStartup failed with error " << res << std::endl;
    }
#endif
    std::cout << "[status] Creating socket..." << std::endl;
    if ((socketfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        return -1;
    }

    std::cout << "[status] Initializing..." << std::endl;
    if (setsockopt(socketfd, SOL_SOCKET, SO_BROADCAST,
                   &trueflag, sizeof(trueflag)) < 0) {
        closeSocket(socketfd);
        return -1;
    }

    memset(&recv_addr, 0, sizeof(recv_addr));
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(PORT);
    recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    std::cout << "[status] Binding..." << std::endl;
    if (bind(socketfd, (struct sockaddr*) &recv_addr, sizeof(recv_addr)) < 0) {
        closeSocket(socketfd);
        return -1;
    }

    std::cout << std::endl;
    std::cout << "Setup successful. Client is listening." << std::endl;
    std::cout << std::endl;

    while (1) {
        char buffer[256] = {};
        if (recvfrom(socketfd, buffer, sizeof(buffer)-1, 0,
            (struct sockaddr*) &recv_addr, &slen) < 0) {
            closeSocket(socketfd);
            return -1;
        }
#ifdef _WIN32
        if (!EnableVTMode()) {
            std::cout << "Unable to enter VT processing mode." << std::endl;
        }
#endif
        std::cout << buffer;
    }

    closeSocket(socketfd);
    return 0;
}