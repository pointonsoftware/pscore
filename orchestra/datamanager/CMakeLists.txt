project (datamanager)

# datamanager lib
add_library (
    datamanager
    STATIC
    # customer management
    customerdata.hpp
    customerdata.cpp
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
    # sales
    salesdata.hpp
    salesdata.cpp
)

target_link_libraries (
    datamanager
    entity
    stackdb
    utility
)