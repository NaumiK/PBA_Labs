set(SRCS
    main.cpp
    myfuncs.cpp
)

option(LAB3_IMPL 0)

if (${LAB3_IMPL} EQUAL 1 OR ${LAB3_IMPL} EQUAL 2)
    list(APPEND SRCS Matrix.cpp)
endif()

add_executable(LAB3 ${SRCS})
target_include_directories(LAB3 PRIVATE ${CMAKE_BINARY_DIR})

if(${LAB3_IMPL} EQUAL 1)
    message(STATUS "Implementation of LAB3 is USE_ONLY_MATRIX")
    target_compile_definitions(LAB3 PRIVATE USE_ONLY_MATRIX)
elseif(${LAB3_IMPL} EQUAL 2)
    message(STATUS "Implementation of LAB3 is USE_VECTOR")
    target_compile_definitions(LAB3 PRIVATE USE_VECTOR)
endif()
