cmake_minimum_required(VERSION 3.9.2)
project(domain)

# set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_STANDARD 17)

option(CI_BUILD "Running in CI" OFF)
if(CI_BUILD)
    # In CI, we need to force select the gold linker for -fsanitize flag
    set(CMAKE_CXX_FLAGS "-Wall -pedantic -Werror -Wno-variadic-macros -Wno-long-long -Wno-shadow -g -O2 -fsanitize=address -fuse-ld=gold -pg")
else()
    set(CMAKE_CXX_FLAGS "-Wall -pedantic -Werror -Wno-variadic-macros -Wno-long-long -Wno-shadow -g -O2 -fsanitize=address -pg")
endif(CI_BUILD)
unset(CI_BUILD CACHE)

add_library(
    core
    STATIC
    userscontroller.cpp
    entities/src/user.cpp
)

include_directories (entities/inc)