project (storage)

# dummy database lib
add_library (
    stackdb
    STATIC
    # in-memory db
    stackdb.hpp
    stackdb.cpp
    table.hpp
)


target_link_libraries (
    stackdb
    entity
)