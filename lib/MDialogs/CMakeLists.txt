project(MDialogs)

set(SRCS 
    dialog.cpp
)
add_library(MDialogs STATIC ${SRCS})
target_link_libraries(MDialogs PUBLIC MIO)