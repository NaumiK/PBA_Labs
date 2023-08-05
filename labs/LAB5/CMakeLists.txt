set(SRCS
    main.cpp
    myfuncs.cpp
)

add_executable(LAB5 ${SRCS})
target_include_directories(LAB5 PRIVATE ${CMAKE_BINARY_DIR})