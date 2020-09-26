project (application)

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
)

target_link_libraries (
    console_app
    databoundary
    domain
    utility
    ${STATIC_LIBS}
)
