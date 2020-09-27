project (storage)

# Databoundary lib
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