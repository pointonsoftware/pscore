project (domain_unittest)

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fprofile-arcs")
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ftest-coverage")
set (CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage -lgcov --coverage ${CMAKE_EXE_LINKER_FLAGS}")

add_executable (
    domain_unittest
    test_main.cpp
    test_auth.cpp
)


target_link_libraries (
    domain_unittest
    auth
    gtest
    gmock
    ${STATIC_LIBS}
)
