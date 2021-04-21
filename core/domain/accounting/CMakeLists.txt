project (accounting)

# domain lib
add_library (
    accounting
    SHARED
    # View
    interface/accountingviewif.hpp
    # Dataprovider
    interface/accountingdataif.hpp
    # Controller
    interface/accountingiface.hpp
    accountingcontroller.hpp
    accountingcontroller.cpp
)

target_link_libraries (
    accounting
    entity
    utility
    validator
    ${MINGW_DEPENDENCY}
)
