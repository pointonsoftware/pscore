project (entity)

# entity lib
add_library (
    entity
    STATIC
    # Entities
    address.hpp
    contactdetails.hpp
    employee.hpp
    employee.cpp
    person.hpp
    person.cpp
    personalid.hpp
    product.hpp
    product.cpp
    user.hpp
    user.cpp
)

target_compile_options(entity PUBLIC "-fPIC")