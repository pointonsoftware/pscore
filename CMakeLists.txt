cmake_minimum_required (VERSION 3.9.2)

set (CORE_VERSION 0.4.9)

if (CMAKE_VERSION VERSION_LESS 3.0)
  project (core C CXX)
  set (PROJECT_VERSION ${CORE_VERSION})
else()
  cmake_policy (SET CMP0048 NEW)
  project (core VERSION ${CORE_VERSION} LANGUAGES CXX C)
endif()

# Version file
set (version_file "${CMAKE_CURRENT_BINARY_DIR}/bin/version")
write_file (${version_file} "[CORE]\nversion=${CORE_VERSION}")


option (BUILD_ALL "Build app and data" ON)
option (BUILD_UNITTEST "Build unit tests" ON)
option (BUILD_LOG_CLIENT "Build socketlogger client" OFF)


# set(CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib CACHE INTERNAL "")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib CACHE INTERNAL "")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin CACHE INTERNAL "")


if(CMAKE_COMPILER_IS_GNUCXX)
# compiler options
set (COMPILER_EXCEPTION
    "-Wno-variadic-macros -Wno-long-long -Wno-shadow -Wno-unknown-pragmas \
     -Wno-unused-result")
message(STATUS "GCC detected, adding compile flags")
set (CMAKE_CXX_FLAGS "-Wall -pedantic -Werror ${COMPILER_EXCEPTION} -O2")
endif(CMAKE_COMPILER_IS_GNUCXX)

if (NOT MINGW)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -pg")
endif ()


# linker options
set (MINGW_DEPENDENCY "")
if (MINGW)
# Warning! This bloats our binary, but we have no other option for mingw
set(MINGW_DEPENDENCY "-static")
endif ()


# directories
include_directories (core)
include_directories (orchestra/datamanager)
include_directories (orchestra/migration)
include_directories (utility)
include_directories (external/datetime/include)

if (BUILD_UNITTEST)
include_directories (external/gtest/googletest/include)
include_directories (external/gtest/googlemock/include)
endif()

add_subdirectory (core/domain)
add_subdirectory (core/entity)
add_subdirectory (core/validator)
add_subdirectory (utility)


# optional builds
if (BUILD_ALL)
message(STATUS "All components enabled")
add_subdirectory (orchestra/application)
add_subdirectory (orchestra/datamanager)
add_subdirectory (orchestra/migration/storage)
endif()

if (BUILD_UNITTEST)
message(STATUS "Unittest enabled")
add_subdirectory (external/gtest)
endif()
