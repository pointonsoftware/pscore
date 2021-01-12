project (common)

# domain lib
add_library (
    domaincommon
    STATIC
    cachecontroller.hpp
    basecontroller.hpp
    librarycommon.hpp
)

target_link_libraries (
    domaincommon
    entity
    ${MINGW_DEPENDENCY}
)
