cmake_minimum_required(VERSION 3.8)
project(server)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp frame/gamesvr.cpp frame/netmgr.cpp)

include_directories(./)
include_directories(./deps/libuv/include)

link_directories(LIBUV ./deps/libuv/lib)

link_libraries(uv pthread)

add_executable(server ${SOURCE_FILES})