cmake_minimum_required(VERSION 3.23)
project(Labs VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)

# version.h
include(cmake/git-hash.cmake)

message("GIT_COMMIT_HASH: ${GIT_COMMIT_HASH}")
##############################
add_subdirectory(lib)
message(STATUS "Collected libs: ${LIBLIST}")
foreach(LIB ${LIBLIST})
    target_include_directories(${LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/${LIB})
    target_include_directories(${LIB} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
endforeach(LIB ${LIBLIST})

add_subdirectory(labs)
message(STATUS "Collected labs: ${LABLIST}")

foreach(LAB ${LABLIST})
    target_include_directories(${LAB} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include")
    target_include_directories(${LAB} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/${LAB}")

    # target_link_libraries(${LAB} ${LIBLIST})
    target_link_libraries(${LAB} MDialogs)
endforeach(LAB ${LABLIST})

#######################