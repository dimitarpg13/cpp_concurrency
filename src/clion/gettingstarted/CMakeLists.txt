cmake_minimum_required(VERSION 3.22)
project(gettingstarted)

set(CMAKE_CXX_STANDARD 14)

add_executable(hello_concurrent_world hello_concurrent_world.cpp)
add_executable(oops oops.cpp)
add_executable(waited_thread waited_thread.cpp)
add_executable(raii_for_thread_waiting raii_for_thread_waiting.cpp)