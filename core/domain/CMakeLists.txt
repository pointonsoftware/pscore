project (domain)

# Domains
add_subdirectory (common)
add_subdirectory (customermgmt)
add_subdirectory (dashboard)
add_subdirectory (employeemgmt)
add_subdirectory (inventory)
add_subdirectory (sales)
add_subdirectory (userlogin)

# Note: the unit test executable is affected by this flag
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

if (MINGW)
    add_compile_definitions(BUILD_CORE_DLL)
endif ()

if (BUILD_UNITTEST)
    set (DOMAIN_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
    add_subdirectory (unittest)
endif()