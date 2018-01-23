cmake_minimum_required(VERSION 2.8)
project(server)

set(CMAKE_CXX_STANDARD 11)

# 添加 c++11 编译选项
if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-std=c++11)
    message(STATUS "optional:-std=c++11")
endif(CMAKE_COMPILER_IS_GNUCXX)

set(SOURCE_FILES main.cpp frame/gamesvr.cpp frame/netmgr.cpp)

include_directories(${PROJECT_SOURCE_DIR})
# INCLUDE PATH
include_directories(${PROJECT_SOURCE_DIR}/deps/libuv/include)

# LIBORARY
link_directories(${PROJECT_SOURCE_DIR}/deps/libuv/lib)

link_libraries(uv pthread rt)

add_executable(server ${SOURCE_FILES})