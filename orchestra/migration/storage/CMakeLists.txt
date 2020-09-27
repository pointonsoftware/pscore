project (storage)

# dummy database lib
add_library (
    dummydata
    STATIC
    # in-memory db
    stackdb.hpp
    stackdb.cpp
)


target_link_libraries (
    dummydata
    entity
)