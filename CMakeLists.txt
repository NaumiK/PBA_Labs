cmake_minimum_required(VERSION 3.23)
project(Labs)

set(CMAKE_CXX_STANDARD 20)

##############################
set(LAB_NUM 6)

set(COMPILE_FILES ${LAB_NUM}/main.cpp)
if (${LAB_NUM} LESS 4)
    list(APPEND COMPILE_FILES ${LAB_NUM}/myfuncs.cpp)
else ()
    list(APPEND COMPILE_FILES ${LAB_NUM}/dialog.cpp ${LAB_NUM}/dialog.hpp ${LAB_NUM}/MIO.cpp ${LAB_NUM}/MExc.cpp)
endif ()


if (${LAB_NUM} EQUAL 4)
    list(APPEND COMPILE_FILES ${LAB_NUM}/MyString.cpp)
endif ()
if (${LAB_NUM} EQUAL 5)
    list(APPEND COMPILE_FILES ${LAB_NUM}/MIO.hpp)
endif ()
if (${LAB_NUM} EQUAL 6)
    list(APPEND COMPILE_FILES ${LAB_NUM}/MLL.cpp)
endif ()

add_executable(Labs ${COMPILE_FILES})

#######################