project (domain_unittest)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
set (CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage -lgcov --coverage ${CMAKE_EXE_LINKER_FLAGS}")

add_executable (
    domain_unittest
    test_main.cpp
    test_login.cpp
)

set (CONSOLE_APP_LINKER_EXCEPTION "")
if (MINGW)
# This is a temporary solution for now, so we can link with the dlls
set (CONSOLE_APP_LINKER_EXCEPTION "-Wl,-allow-multiple-definition")
endif ()

target_link_libraries (
    domain_unittest
    loginmod
    gtest
    gmock
    ${MINGW_DEPENDENCY}
    ${CONSOLE_APP_LINKER_EXCEPTION}
)
