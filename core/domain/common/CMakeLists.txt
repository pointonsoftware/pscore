project (common)

# domain lib
add_library (
    domaincommon
    STATIC
    cachecontroller.hpp
    basecontroller.hpp
    librarycommon.hpp
)

set_target_properties(domaincommon PROPERTIES LINKER_LANGUAGE CXX)