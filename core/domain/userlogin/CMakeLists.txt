project (userlogin)

# domain lib
add_library (
    logindomain
    STATIC
    # Common
    # defines.hpp
    # View
    interface/loginviewif.hpp
    # Dataprovider
    interface/logindataif.hpp
    # Controllers
    interface/logincontrolif.hpp
    logincontroller.hpp
    logincontroller.cpp
)

target_link_libraries (
    logindomain
    entity
    utility
)