project (sales)

# domain lib
add_library (
    sales
    SHARED
    # View
    interface/salesviewif.hpp
    # Dataprovider
    interface/salesdataif.hpp
    # Controller
    interface/salesiface.hpp
    salecomputer.hpp
    salecomputer.cpp
    salescontroller.hpp
    salescontroller.cpp
)

target_link_libraries (
    sales
    entity
    utility
    validator
    ${MINGW_DEPENDENCY}
)
