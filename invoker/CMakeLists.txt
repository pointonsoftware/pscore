project (invoker)

add_subdirectory (domain)
add_subdirectory (entity)

if (BUILD_UNITTEST)
    add_subdirectory (unittest)
endif()