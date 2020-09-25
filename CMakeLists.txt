cmake_minimum_required (VERSION 3.9.2)
project (core C CXX)


option (BUILD_ALL "Build app and data" ON)
option (BUILD_UNITTEST "Build unit tests" ON)
option (BUILD_LOG_CLIENT "Build socketlogger client" OFF)


# set(CMAKE_BUILD_TYPE Debug)
set (CMAKE_CXX_STANDARD 17)
set (CMAKE_CXX_STANDARD_REQUIRED ON)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib CACHE INTERNAL "")
set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib CACHE INTERNAL "")
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin CACHE INTERNAL "")


# compiler options
set (COMPILER_EXCEPTION
    "-Wno-variadic-macros -Wno-long-long -Wno-shadow -Wno-unknown-pragmas \
     -Wno-unused-result")
set (CMAKE_CXX_FLAGS "-Wall -pedantic -Werror ${COMPILER_EXCEPTION} -O2")

if (NOT MINGW)
    set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -pg")
endif ()


# linker options
set (STATIC_LIBS "")
if (MINGW)
    # Warning! This bloats our binary, but we have no other option for mingw
    set(STATIC_LIBS "-static-libgcc -static-libstdc++ -lstdc++ --static")
endif ()


# directories
include_directories (invoker)
include_directories (utility)
include_directories (databoundary)

if (BUILD_UNITTEST)
include_directories (mock)
include_directories (external/gtest/googletest/include)
include_directories (external/gtest/googlemock/include)
endif()

add_subdirectory (invoker)
add_subdirectory (utility)


# optional builds
if (BUILD_ALL)
message(STATUS "All components enabled")
add_subdirectory (application)
add_subdirectory (databoundary)
endif()

if (BUILD_UNITTEST)
message(STATUS "Unittest enabled")
add_subdirectory (external/gtest)
endif()
