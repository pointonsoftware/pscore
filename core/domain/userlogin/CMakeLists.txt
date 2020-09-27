project (userlogin)

# domain lib
add_library (
    auth
    STATIC
    # Common
    # defines.hpp
    # Views
    interface/authviewif.hpp
    # Dataproviders
    interface/authdataif.hpp
    # Controllers
    authcontroller.hpp
    authcontroller.cpp
)

target_link_libraries (
    auth
    entity
    utility
)