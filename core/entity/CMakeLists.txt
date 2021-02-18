project (entity)

# entity lib
add_library (
    entity
    STATIC
    # Entities
    address.hpp
    contactdetails.hpp
    customer.hpp
    customer.cpp
    employee.hpp
    employee.cpp
    person.hpp
    person.cpp
    personalid.hpp
    product.hpp
    product.cpp
    sale.hpp
    sale.cpp
    saleitem.hpp
    saleitem.cpp
    uom.hpp
    user.hpp
    user.cpp
)

target_compile_options(entity PUBLIC "-fPIC")