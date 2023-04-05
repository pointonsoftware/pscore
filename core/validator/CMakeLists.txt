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
    employeevalidator.hpp
    employeevalidator.cpp
    personalidvalidator.hpp
    personalidvalidator.cpp
    personvalidator.hpp
    personvalidator.cpp
    productvalidator.hpp
    productvalidator.cpp
    uservalidator.hpp
    uservalidator.cpp
    validator.hpp
)

target_link_libraries (
    validator
    entity
    utility
    ${MINGW_DEPENDENCY}
)

if (NOT MSVC)
    target_compile_options(validator PUBLIC "-fPIC")
endif()