set(SRCS
    main.cpp
    myfuncs.cpp
)

add_executable(LAB3 ${SRCS})
target_include_directories(LAB3 PRIVATE ${CMAKE_BINARY_DIR})
