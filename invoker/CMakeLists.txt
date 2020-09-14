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
    domain/interface/view/authviewif.hpp
    # Dataproviders
    domain/interface/dataprovider/dataproviderif.hpp
    domain/interface/dataprovider/authdataif.hpp
    # Controllers
    domain/controller/authcontroller.hpp
    domain/controller/authcontroller.cpp
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