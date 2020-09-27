project (userlogin)

# domain lib
add_library (
    logindomain
    STATIC
    # View
    interface/loginviewif.hpp
    # Dataprovider
    interface/logindataif.hpp
    # Controller
    interface/logincontrolif.hpp
    logincontroller.hpp
    logincontroller.cpp
)

target_link_libraries (
    logindomain
    entity
    utility
)