/**************************************************************************//**
*         Copyright (C) Pointon Software - All Rights Reserved                *
*                                                                             *
*   Unauthorized copying of this file via any medium is strictly prohibited   *
*   Proprietary and confidential                                              *
*                                                                             *
*   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020               *
*                                                                             *
******************************************************************************/
#include <iostream>
#include <controllers/authcontroller.hpp>
#include <logger/loghelper.hpp>

int main() {
    domain::authentication::AuthController aut (nullptr, nullptr);
    std::cout << "Hello, Welcome Core!" << std::endl;
    LOG_DEBUG("Your logger is now alive!");
    return 0;
}