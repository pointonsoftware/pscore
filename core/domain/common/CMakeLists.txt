project (common)

# domain lib
add_library (
    domaincommon
    STATIC
    librarycommon.hpp
    basecontroller.hpp
)

target_link_libraries (
    domaincommon
    entity
    ${MINGW_DEPENDENCY}
)
