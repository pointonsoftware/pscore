project (logclient)

# Logger client
add_executable (
    log_client_app
    logclient.cpp
)

if (MINGW)
    target_link_libraries (
        log_client_app
        "-lws2_32"
        ${MINGW_DEPENDENCY}
    )
endif ()
