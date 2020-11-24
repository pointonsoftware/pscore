project (userlogin)

# domain lib
add_library (
    loginmod
    SHARED
    # View
    interface/loginviewif.hpp
    # Dataprovider
    interface/logindataif.hpp
    # Controller
    interface/loginiface.hpp
    logincontroller.hpp
    logincontroller.cpp
)

target_link_libraries (
    loginmod
    entity
    utility
    validator
    ${MINGW_DEPENDENCY}
)