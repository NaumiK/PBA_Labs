set(SRCS
    main.cpp
    myfuncs.cpp
    MyString.cpp
)

add_executable(LAB4 ${SRCS})
target_include_directories(LAB4 PRIVATE ${CMAKE_BINARY_DIR})