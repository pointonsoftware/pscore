project (entity)

# Includes root directory
include_directories(.)

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
    user.hpp
    user.cpp
    # Validators
    validator/addressvalidator.hpp
    validator/addressvalidator.cpp
    validator/contactdetailsvalidator.hpp
    validator/contactdetailsvalidator.cpp
    validator/personalidvalidator.hpp
    validator/personalidvalidator.cpp
    validator/personvalidator.hpp
    validator/personvalidator.cpp
)

target_compile_options(entity PUBLIC "-fPIC")