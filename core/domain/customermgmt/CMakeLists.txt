project (inventory)

# domain lib
add_library (
    customermgmt
    SHARED
    # View
    interface/customermgmtviewif.hpp
    # Dataprovider
    interface/customermgmtdataif.hpp
    # Controller
    interface/customermgmtiface.hpp
    customermgmtcontroller.hpp
    customermgmtcontroller.cpp
)

target_link_libraries (
    customermgmt
    entity
    utility
    validator
    ${MINGW_DEPENDENCY}
)
