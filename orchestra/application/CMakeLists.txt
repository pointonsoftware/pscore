project (application)

include_directories(screen)

add_executable (
    console_app
    main.cpp
    # Control
    flowcontroller.hpp
    flowcontroller.cpp
    # Common screens
    screen/screeniface.hpp
    screen/screencommon.hpp
    screen/screencommon.cpp
    # Login screen
    screen/login/loginscreen.hpp
    screen/login/loginscreen.cpp
    # Back office screen
    screen/backoffice/dashboard.hpp
    screen/backoffice/dashboard.cpp
)

target_link_libraries (
    console_app
    logindomain
    datamanager
    dashboard
)
