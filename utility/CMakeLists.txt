project (utility)

include_directories (inc)

# Core lib
add_library (
    utility
    STATIC
    src/logger/loghelper.cpp
    src/logger/consolelog.cpp
)
