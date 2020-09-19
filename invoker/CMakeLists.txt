project (invoker)

# include_directories (domain)
# include_directories (entity)

# Core lib
add_library (
    invoker
    STATIC
    # Root public
    domain/defines.hpp
    # Views
    domain/userlogin/interface/authviewif.hpp
    # Dataproviders
    domain/userlogin/interface/authdataif.hpp
    # Controllers
    domain/userlogin/authcontroller.hpp
    domain/userlogin/authcontroller.cpp
    # Entities
    entity/address.hpp
    entity/contactdetails.hpp
    entity/employee.hpp
    entity/employee.cpp
    entity/person.hpp
    entity/person.cpp
    entity/personalid.hpp
)

if (BUILD_UNITTEST)
    add_subdirectory (unittest)
endif()