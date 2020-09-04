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
    inc/entities/address.hpp
    inc/entities/contactdetails.hpp
    inc/entities/employee.hpp
    src/entities/employee.cpp
    inc/entities/person.hpp
    src/entities/person.cpp
    inc/entities/personalid.hpp
)

if (BUILD_UNITTEST)
    add_subdirectory (unittest)
endif()