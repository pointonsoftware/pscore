project (utility)

include_directories (inc)

# Core lib
add_library (
    utility
    STATIC
    # logger
    inc/logger/loggeriface.hpp
    src/logger/loggeriface.cpp
    inc/logger/loghelper.hpp
    src/logger/loghelper.cpp
    inc/logger/consolelog.hpp
    src/logger/consolelog.cpp
    inc/logger/filelog.hpp
    src/logger/filelog.cpp
    inc/logger/socketlog.hpp
    src/logger/socketlog.cpp
    # fileio
    inc/fileio/fileio.hpp
    src/fileio/fileio.cpp
    # cfg
    inc/cfg/configiface.hpp
    inc/cfg/config.hpp
    src/cfg/config.cpp
)
