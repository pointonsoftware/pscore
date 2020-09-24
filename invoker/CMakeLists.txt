project (invoker)

#include_directories (domain)
#include_directories (entity)
add_subdirectory (domain)
add_subdirectory (entity)

if (BUILD_UNITTEST)
    add_subdirectory (unittest)
endif()