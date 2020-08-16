/**************************************************************************//**
*         Copyright (C) Pointon Software - All Rights Reserved                *
*                                                                             *
*   Unauthorized copying of this file via any medium is strictly prohibited   *
*   Proprietary and confidential                                              *
*                                                                             *
*   Written by Ben Ziv <pointonsoftware@gmail.com>, August 2020               *
*                                                                             *
******************************************************************************/

#include <inc/authcontroller.hpp>

namespace domain {
namespace controllers {

AuthController::AuthController(std::unique_ptr<AuthViewIface>&& view, 
                     std::unique_ptr<AuthDataProviderIface>&& dataprovider)
: mView(std::move(view)), mDataProvider(std::move(dataprovider)) {
    // Empty for now
}

bool AuthController::login(const std::string& pin) {
    // Check if pin is empty
    // Check if pin is numeric
    // Call authenticate
    return true;
}

status::General AuthController::authenticate(const std::string& pin) {
    // Check if dataprovider is ready; else throw
    // Check pin in dataprovider
    return status::General::SUCCESS;
}

}  // controllers
}  // domain