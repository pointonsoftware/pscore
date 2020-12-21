project (datamanager)

# datamanager lib
add_library (
    datamanager
    STATIC
    # dashboard
    dashboarddata.hpp
    dashboarddata.cpp
    # employee management
    employeedata.hpp
    employeedata.cpp
    # inventory control
    inventorydata.hpp
    inventorydata.cpp
    # userlogin
    logindata.hpp
    logindata.cpp
)

target_link_libraries (
    datamanager
    entity
    stackdb
    utility
)