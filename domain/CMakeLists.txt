project (domain)

include_directories (inc)
include_directories (public)

# Core lib
add_library (
    core
    STATIC
    # Root public
    public/defines.hpp
    # View
    public/views/authviewif.hpp
    # Dataprovider
    public/dataproviders/dataproviderif.hpp
    public/dataproviders/authdataif.hpp
    # Controller
    public/controllers/authcontroller.hpp
    src/controllers/authcontroller.cpp
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