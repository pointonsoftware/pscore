project (storage)

# dummy database lib
add_library (
    stackdb
    STATIC
    # in-memory db
    stackdb.hpp
    stackdb.cpp
)


target_link_libraries (
    stackdb
    entity
)