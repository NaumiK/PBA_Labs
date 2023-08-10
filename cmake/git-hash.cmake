find_program(GIT git HITS ${GIT_PATH})

if (NOT GIT)
    message(STATUS "Probably need to specify GIT_PATH")
    set(GIT_COMMIT_HASH "GitNotFound")
else()
    execute_process(
        COMMAND ${GIT} log -1 --format=%h
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        OUTPUT_VARIABLE GIT_COMMIT_HASH
        OUTPUT_STRIP_TRAILING_WHITESPACE
    )
    if ("${GIT_COMMIT_HASH}" STREQUAL "")
        set(GIT_COMMIT_HASH "GitNotFound")
    endif()
endif()


configure_file(
    ${CMAKE_SOURCE_DIR}/version.h.in
    ${CMAKE_BINARY_DIR}/version.h
)