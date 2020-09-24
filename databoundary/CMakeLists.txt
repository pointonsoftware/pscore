project (databoundary)

# Databoundary lib
add_library (
    databoundary
    STATIC
    # in-memory db
    stackdb.hpp
    stackdb.cpp
    # userlogin
    logindata/authdata.hpp
    logindata/authdata.cpp
)


target_link_libraries (
    databoundary
    entity
    utility
)