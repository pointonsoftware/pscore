project (inventory)

# domain lib
add_library (
    inventory
    SHARED
    # View
    interface/inventoryviewif.hpp
    # Dataprovider
    interface/inventorydataif.hpp
    # Controller
    interface/inventoryiface.hpp
    inventorycontroller.hpp
    inventorycontroller.cpp
)

target_link_libraries (
    inventory
    entity
    utility
    validator
    ${MINGW_DEPENDENCY}
)
