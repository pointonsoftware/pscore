project (domain_unittest)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
set (CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage -lgcov --coverage ${CMAKE_EXE_LINKER_FLAGS}")

set (SOURCES_UNDER_TEST
    ${DOMAIN_DIRECTORY}/accounting/accountingcontroller.cpp
    ${DOMAIN_DIRECTORY}/customermgmt/customermgmtcontroller.cpp
    ${DOMAIN_DIRECTORY}/dashboard/dashboardcontroller.cpp
    ${DOMAIN_DIRECTORY}/employeemgmt/employeecontroller.cpp
    ${DOMAIN_DIRECTORY}/inventory/inventorycontroller.cpp
    ${DOMAIN_DIRECTORY}/pos/salecomputer.cpp
    ${DOMAIN_DIRECTORY}/userlogin/logincontroller.cpp
)

add_executable (
    domain_unittest
    ${SOURCES_UNDER_TEST}
    # mocks
    mock/customermgmt/customermgmtdatamock.hpp
    mock/customermgmt/customermgmtviewmock.hpp
    mock/dashboard/dashboarddatamock.hpp
    mock/dashboard/dashboardviewmock.hpp
    mock/employeemgmt/empmgmtdatamock.hpp
    mock/employeemgmt/empmgmtviewmock.hpp
    mock/inventory/inventorydatamock.hpp
    mock/inventory/inventoryviewmock.hpp
    mock/login/logindatamock.hpp
    mock/login/loginviewmock.hpp
    mock/accounting/accountingdatamock.hpp
    mock/accounting/accountingviewmock.hpp
    # test suites
    test_main.cpp
    test_customermgmt.cpp
    test_dashboard.cpp
    test_empmgmt.cpp
    test_inventory.cpp
    test_login.cpp
    test_accounting.cpp
    test_salecomputer.cpp
)

set (UNIT_TEST_LINKER_EXCEPTION "")
if (MINGW)
# This is a temporary solution for now, so we can link with the dlls
set (UNIT_TEST_LINKER_EXCEPTION "-Wl,-allow-multiple-definition")
endif ()

target_link_libraries (
    domain_unittest
    domaincommon
    entity
    validator
    gtest
    gmock
    ${MINGW_DEPENDENCY}
    ${UNIT_TEST_LINKER_EXCEPTION}
)
