project (application)

include_directories(screen)

add_executable (
    console_app
    main.cpp
    # Common screens
    screen/viewcommon.hpp
    screen/viewcommon.cpp
    # Login screen
    screen/login/authview.hpp
    screen/login/authview.cpp
)

target_link_libraries (
    console_app
    domain
    utility
    databoundary
    ${STATIC_LIBS}
)
