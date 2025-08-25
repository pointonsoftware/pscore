project (domain)

if (MINGW OR MSVC)
    add_compile_definitions(BUILD_CORE_DLL)
endif ()

# Domains
add_subdirectory (accounting)
add_subdirectory (common)
add_subdirectory (customermgmt)
add_subdirectory (dashboard)
add_subdirectory (employeemgmt)
add_subdirectory (inventory)
add_subdirectory (pos)
add_subdirectory (userlogin)

if (NOT MSVC)
    # Note: the unit test executable is affected by this flag
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")
endif()

if (BUILD_UNITTEST)
    set (DOMAIN_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
    add_subdirectory (unittest)
endif()