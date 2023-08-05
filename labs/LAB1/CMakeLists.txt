set(SRCS
    main.cpp
    myfuncs.cpp
)

add_executable(LAB1 ${SRCS})
target_include_directories(LAB1 PRIVATE ${CMAKE_BINARY_DIR})
