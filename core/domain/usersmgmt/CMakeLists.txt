project (usersmgmt)

# domain lib
add_library (
    usersmgmt
    SHARED
    # View
    interface/usersmgmtviewif.hpp
    # Dataprovider
    interface/usersmgmtdataif.hpp
    # Controller
    interface/usersmgmtiface.hpp
    userscontroller.hpp
    userscontroller.cpp
)

target_link_libraries (
    usersmgmt
    entity
    utility
    ${MINGW_DEPENDENCY}
)
