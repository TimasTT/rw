add_executable(main main.cpp)

target_include_directories(main PUBLIC
        ../rw_lib/include)
target_link_libraries (main ${CMAKE_THREAD_LIBS_INIT} rw)