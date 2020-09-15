project (application)

add_executable (
    console_app
    main.cpp
)

#add_dependencies (console_app core)

target_link_libraries (
    console_app
    invoker
    utility
    ${STATIC_LIBS}
)
