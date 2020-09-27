project (logindata)

# logindata lib
add_library (
    logindata
    STATIC
    # userlogin
    authdata.hpp
    authdata.cpp
)


target_link_libraries (
    logindata
    dummydata
    entity
    utility
)