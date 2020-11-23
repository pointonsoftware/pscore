project (validator)

# validator lib
add_library (
    validator
    STATIC
    # Validators
    addressvalidator.hpp
    addressvalidator.cpp
    contactdetailsvalidator.hpp
    contactdetailsvalidator.cpp
    personalidvalidator.hpp
    personalidvalidator.cpp
    personvalidator.hpp
    personvalidator.cpp
    uservalidator.hpp
    uservalidator.cpp
    validator.hpp
)

target_compile_options(validator PUBLIC "-fPIC")