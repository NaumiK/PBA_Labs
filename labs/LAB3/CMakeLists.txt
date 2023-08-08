set(SRCS
    main.cpp
    myfuncs.cpp
    Matrix.cpp
)

add_executable(LAB3 ${SRCS})
target_include_directories(LAB3 PRIVATE ${CMAKE_BINARY_DIR})

option(LAB3_IMPL 0)
if(${LAB3_IMPL} EQUAL 1)
    target_compile_definitions(LAB3 PRIVATE USE_ONLY_MATRIX)
elseif(${LAB3_IMPL} EQUAL 2)
    target_compile_definitions(LAB3 PRIVATE USE_VECTOR)
endif()
