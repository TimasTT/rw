add_library(rw STATIC
        include/rw.hpp
        source/rw.cpp)

target_include_directories(rw PUBLIC
        include)
target_link_libraries (rw ${CMAKE_THREAD_LIBS_INIT})