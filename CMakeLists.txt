cmake_minimum_required (VERSION 3.9.2)
project (core C CXX)

option (BUILD_ALL "Build app and data" OFF)
option (BUILD_UNITTEST "Build unit tests" OFF)

# set(CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib CACHE INTERNAL "")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib CACHE INTERNAL "")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin CACHE INTERNAL "")
set (CMAKE_CXX_FLAGS "-Wall -pedantic -Werror -Wno-variadic-macros -Wno-long-long -Wno-shadow -g -O2 -fsanitize=address -pg")

if (BUILD_UNITTEST)
    message(STATUS "Unittest enabled")
    add_compile_options(-ftest-coverage -fprofile-arcs -fno-inline)
    add_link_options(-fprofile-arcs -ftest-coverage -lgcov)
endif()

include_directories (domain/inc)
include_directories (domain/public)
add_subdirectory (domain)

if (BUILD_ALL)
    message(STATUS "Building all components")
    add_subdirectory (application)
    add_subdirectory (databoundary)
endif()


