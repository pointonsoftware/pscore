project (domain_unittest)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
set (CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage -lgcov --coverage ${CMAKE_EXE_LINKER_FLAGS}")

set (SOURCES_UNDER_TEST
    ${DOMAIN_DIRECTORY}/dashboard/dashboardcontroller.cpp
    ${DOMAIN_DIRECTORY}/userlogin/logincontroller.cpp
)

add_executable (
    domain_unittest
    ${SOURCES_UNDER_TEST}
    test_main.cpp
    test_dashboard.cpp
    test_login.cpp
)

set (UNIT_TEST_LINKER_EXCEPTION "")
if (MINGW)
# This is a temporary solution for now, so we can link with the dlls
set (UNIT_TEST_LINKER_EXCEPTION "-Wl,-allow-multiple-definition")
endif ()

target_link_libraries (
    domain_unittest
    entity
    validator
    gtest
    gmock
    ${MINGW_DEPENDENCY}
    ${UNIT_TEST_LINKER_EXCEPTION}
)
