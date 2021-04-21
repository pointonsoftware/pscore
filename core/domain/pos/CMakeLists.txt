project (pos)

# domain lib
add_library (
    pos
    SHARED
    # View
    interface/posviewif.hpp
    # Dataprovider
    interface/posdataif.hpp
    # Controller
    interface/posiface.hpp
    salecomputer.hpp
    salecomputer.cpp
)

target_link_libraries (
    pos
    entity
    utility
    validator
    ${MINGW_DEPENDENCY}
)
