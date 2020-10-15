project (employeemgmt)

# domain lib
add_library (
    empmgmt
    SHARED
    # View
    interface/employeemgmtviewif.hpp
    # Dataprovider
    interface/employeemgmtdataif.hpp
    # Controller
    interface/employeemgmtiface.hpp
    employeecontroller.hpp
    employeecontroller.cpp
)

target_link_libraries (
    empmgmt
    entity
    utility
    ${MINGW_DEPENDENCY}
)
