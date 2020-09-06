/**************************************************************************************************
*                      Copyright (C) Pointon Software - All Rights Reserved                       *
*                                                                                                 *
*             Unauthorized copying of this file via any medium is strictly prohibited             *
*                                  Proprietary and confidential                                   *
*                                                                                                 *
*                   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020                   *
*                                                                                                 *
**************************************************************************************************/

/* NOTE!
 * When updating the std::cin's of console_app, update ci/automation_input.txt as well.
*/

#include <iostream>
#include <controller/authcontroller.hpp>
#include <logger/loghelper.hpp>

int main() {
    domain::authentication::AuthController auth(nullptr, nullptr);
    std::string name;

    std::cout << "Hi there, Welcome to Core! What's your name?" << std::endl;
    std::cin >> name;

    LOG_DEBUG("Hello %s, I'm using the core logger to print this debug message!", name.c_str());
    return 0;
}