project (domain)

# domain lib
add_library (
    domain
    STATIC
    # Root public
    defines.hpp
    # Views
    userlogin/interface/authviewif.hpp
    # Dataproviders
    userlogin/interface/authdataif.hpp
    # Controllers
    userlogin/authcontroller.hpp
    userlogin/authcontroller.cpp
)

target_link_libraries (
    domain
    entity
    utility
)