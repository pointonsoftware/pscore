project (datamanager)

# datamanager lib
add_library (
    datamanager
    STATIC
    # userlogin
    logindata.hpp
    logindata.cpp
)

target_link_libraries (
    datamanager
    dummydata
    entity
    utility
)