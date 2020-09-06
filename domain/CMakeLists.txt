project (domain)

include_directories (inc)
include_directories (public)

# Core lib
add_library (
    core
    STATIC
    # Root public
    public/defines.hpp
    # Views
    public/view/authviewif.hpp
    # Dataproviders
    public/dataprovider/dataproviderif.hpp
    public/dataprovider/authdataif.hpp
    # Controllers
    public/controller/authcontroller.hpp
    src/controller/authcontroller.cpp
    # Entities
    inc/entity/address.hpp
    inc/entity/contactdetails.hpp
    inc/entity/employee.hpp
    src/entity/employee.cpp
    inc/entity/person.hpp
    src/entity/person.cpp
    inc/entity/personalid.hpp
)

if (BUILD_UNITTEST)
    add_subdirectory (unittest)
endif()