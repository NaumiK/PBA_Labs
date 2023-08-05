cmake_minimum_required(VERSION 3.23)
project(Labs)

set(CMAKE_CXX_STANDARD 20)

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