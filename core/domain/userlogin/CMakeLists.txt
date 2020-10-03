project (userlogin)

# domain lib
add_library (
    loginmod
    SHARED
    # View
    interface/loginviewif.hpp
    # Dataprovider
    interface/logindataif.hpp
    # Controller
    interface/loginiface.hpp
    logincontroller.hpp
    logincontroller.cpp
)

if (MINGW)
add_compile_definitions(BUILD_CORE_DLL)
endif ()

target_compile_options(loginmod PUBLIC "-fPIC")

target_link_libraries (
    loginmod
    entity
    utility
    ${MINGW_DEPENDENCY}
)