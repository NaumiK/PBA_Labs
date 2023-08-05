set(SRCS
    main.cpp
    myfuncs.cpp
)

add_executable(LAB2 ${SRCS})
target_include_directories(LAB2 PRIVATE ${CMAKE_BINARY_DIR})
