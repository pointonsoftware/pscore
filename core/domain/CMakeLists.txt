project (domain)

# Domains
add_subdirectory (userlogin)

if (BUILD_UNITTEST)
    include_directories (.)
    add_subdirectory (unittest)
endif()