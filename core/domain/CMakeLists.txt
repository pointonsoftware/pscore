project (domain)

# Domains
add_subdirectory (dashboard)
add_subdirectory (userlogin)
add_subdirectory (usersmgmt)

# Note: the unit test executable is affected by this flag
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fPIC")

if (MINGW)
    add_compile_definitions(BUILD_CORE_DLL)
endif ()

if (BUILD_UNITTEST)
    add_subdirectory (unittest)
endif()