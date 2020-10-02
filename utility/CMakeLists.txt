project (utility)

# Core lib
add_library (
    utility
    STATIC
    # common utility
    general.hpp
    # logger
    logger/loggeriface.hpp
    logger/loggeriface.cpp
    logger/loghelper.hpp
    logger/loghelper.cpp
    logger/consolelog.hpp
    logger/consolelog.cpp
    logger/filelog.hpp
    logger/filelog.cpp
    logger/socketlog.hpp
    logger/socketlog.cpp
    # fileio
    fileio/fileio.hpp
    fileio/fileio.cpp
    # cfg
    cfg/configiface.hpp
    cfg/config.hpp
    cfg/config.cpp
)

if (MINGW)
target_link_libraries (utility "-lws2_32")
endif ()

# Uncomment the condition below if we dont want to build the logclient always
# if (BUILD_LOG_CLIENT)
add_subdirectory (logclient)
# endif()
