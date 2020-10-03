project (dashboard)

# domain lib
add_library (
    dashboard
    SHARED
    # View
    # Dataprovider
    # Controller
    interface/dashboardiface.hpp
    dashboardcontroller.hpp
    dashboardcontroller.cpp
)

if (MINGW)
add_compile_definitions(BUILD_CORE_DLL)
endif ()

target_compile_options(dashboard PUBLIC "-fPIC")

target_link_libraries (
    dashboard
    entity
    utility
    ${MINGW_DEPENDENCY}
)
