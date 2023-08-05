set(SRCS
    main.cpp
    myfuncs.cpp
    MLL.cpp
)

add_executable(LAB6 ${SRCS})
target_include_directories(LAB6 PRIVATE ${CMAKE_BINARY_DIR})