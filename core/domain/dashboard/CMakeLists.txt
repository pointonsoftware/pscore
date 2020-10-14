project (dashboard)

# domain lib
add_library (
    dashboard
    SHARED
    # View
    interface/dashboardviewif.hpp
    # Dataprovider
    interface/dashboarddataif.hpp
    # Controller
    interface/dashboardiface.hpp
    dashboardcontroller.hpp
    dashboardcontroller.cpp
)

target_link_libraries (
    dashboard
    entity
    utility
    ${MINGW_DEPENDENCY}
)
