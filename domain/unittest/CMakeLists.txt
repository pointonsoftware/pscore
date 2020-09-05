project (domain_unittest)

add_executable(domain_unittest
    test_main.cpp
    test_auth.cpp
)

# add_library(gtest SHARED IMPORTED)
# set_target_properties(gtest PROPERTIES
#   IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/external/googletest/lib/libgtest.a"
# )

target_link_libraries (
    domain_unittest
    core
    gtest
)