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

target_compile_options(dashboard PUBLIC "-fPIC")

target_link_libraries (
    dashboard
    entity
    utility
)