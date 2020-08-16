cmake_minimum_required(VERSION 3.9.2)
project(domain)


# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)


#ADD_SUBDIRECTORY(entities)
#ADD_SUBDIRECTORY(controller)
#ADD_SUBDIRECTORY(unittest)


include_directories (entities)
include_directories (controllers)
include_directories (public)


# Core lib
add_library(
    core
    STATIC
    controllers/src/authcontroller.cpp
    entities/src/employee.cpp
    entities/src/person.cpp
)

# Unit test
#add_executable(
#    console_app
#    test_main.cpp
#    src/userscontroller.cpp
#    src/user.cpp
#)


option(CI_BUILD "Running in CI" OFF)
if(CI_BUILD)
    # In CI, we need to force select the gold linker for -fsanitize flag
    set(CMAKE_CXX_FLAGS "-Wall -pedantic -Werror -Wno-variadic-macros -Wno-long-long -Wno-shadow -g -O2 -fsanitize=address -fuse-ld=gold -pg")
else()
    set(CMAKE_CXX_FLAGS "-Wall -pedantic -Werror -Wno-variadic-macros -Wno-long-long -Wno-shadow -g -O2 -fsanitize=address -pg")
endif(CI_BUILD)
unset(CI_BUILD CACHE)