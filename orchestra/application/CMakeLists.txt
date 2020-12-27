project (application)

include_directories(screen)
include_directories(utility)

add_executable (
    console_app
    main.cpp
    # Control
    flowcontroller.hpp
    flowcontroller.cpp
    # Common screens
    screen/informationscreen.hpp
    screen/informationscreen.cpp
    screen/screeniface.hpp
    # Back office screen
    screen/backoffice/dashboardscreen.hpp
    screen/backoffice/dashboardscreen.cpp
    screen/backoffice/empmgmtscreen.hpp
    screen/backoffice/empmgmtscreen.cpp
    screen/backoffice/inventoryscreen.hpp
    screen/backoffice/inventoryscreen.cpp
    # Login screen
    screen/login/loginscreen.hpp
    screen/login/loginscreen.cpp
    # Utility
    utility/fieldhelper.hpp
    utility/idgenerator.hpp
    utility/idgenerator.cpp
    utility/screencommon.hpp
    utility/screencommon.cpp
)

set (CONSOLE_APP_LINKER_EXCEPTION "")
if (MINGW)
# This is a temporary solution for now, so we can link with the dlls
set (CONSOLE_APP_LINKER_EXCEPTION "-Wl,-allow-multiple-definition")
endif ()

target_link_libraries (
    console_app
    dashboard
    datamanager
    empmgmt
    inventory
    loginmod
    ${MINGW_DEPENDENCY}
    ${CONSOLE_APP_LINKER_EXCEPTION}
)
