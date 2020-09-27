project (application)

include_directories(presenter)
include_directories(screen)

add_executable (
    console_app
    main.cpp
    # Control
    presenter/flowcontroller.hpp
    presenter/flowcontroller.cpp
    # Common screens
    screen/viewcommon.hpp
    screen/viewcommon.cpp
    # Login screen
    screen/login/authview.hpp
    screen/login/authview.cpp
    # Back office screen
    screen/backoffice/dashboard.hpp
    screen/backoffice/dashboard.cpp
)

target_link_libraries (
    console_app
    auth
    logindata
    ${STATIC_LIBS}
)
