project (domain_unittest)

add_compile_options(-ftest-coverage -fprofile-arcs -fno-inline)
add_link_options(-fprofile-arcs -ftest-coverage -lgcov)

add_executable(domain_unittest
    test_main.cpp
    test_auth.cpp
)

target_link_libraries (
    domain_unittest
    core
    gtest
)