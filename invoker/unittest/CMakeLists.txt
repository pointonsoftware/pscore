project (domain_unittest)

add_compile_options(-ftest-coverage -fprofile-arcs -fno-inline)
set(CMAKE_EXE_LINKER_FLAGS "-fprofile-arcs -ftest-coverage -lgcov ${CMAKE_EXE_LINKER_FLAGS}")

add_executable(domain_unittest
    test_main.cpp
    test_auth.cpp
)

target_link_libraries (
    domain_unittest
    invoker
    gtest
)