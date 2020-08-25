project (domain)

include_directories (inc)
include_directories (public)

# Core lib
add_library (
    core
    STATIC
    src/controllers/authcontroller.cpp
    src/entities/employee.cpp
    src/entities/person.cpp
)

if (BUILD_UNITTEST)
    add_subdirectory (unittest)
endif()