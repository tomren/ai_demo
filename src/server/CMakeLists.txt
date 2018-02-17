cmake_minimum_required(VERSION 2.8)
project(server)

set (CMAKE_CXX_STANDARD 11)

# 添加 c++11 编译选项
if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-std=c++11)
    message(STATUS "optional:-std=c++11")
endif(CMAKE_COMPILER_IS_GNUCXX)

set(SOURCE_FILES 
                main.cpp globals.hpp 
                frame/game_server.hpp frame/game_server.cpp 
                frame/net_connect.hpp frame/net_connect.cpp 
                frame/net_client.hpp frame/net_client.cpp frame/net_server.hpp frame/net_server.cpp 
                frame/net_manager.hpp frame/net_manager.cpp)

include_directories(${PROJECT_SOURCE_DIR})
# INCLUDE PATH
include_directories(${PROJECT_SOURCE_DIR}/deps/libuv/include)
include_directories(${PROJECT_SOURCE_DIR}/deps/msgpack/include)

# LIBORARY
link_directories(${PROJECT_SOURCE_DIR}/deps/libuv/lib)
link_directories(${PROJECT_SOURCE_DIR}/deps/msgpack/lib)

if (CMAKE_SYSTEM_NAME MATCHES "Linux")
    link_libraries(msgpack uv pthread rt)
elseif(CMAKE_SYSTEM_NAME MATCHES "Windows")
    link_libraries(msgpack libuvd iphlpapi psapi ws2_32 userenv)
endif (CMAKE_SYSTEM_NAME MATCHES "Linux")

file(GLOB FRAME_HPP "${PROJECT_SOURCE_DIR}/frame/*.hpp")
file(GLOB FRAME_CPP "${PROJECT_SOURCE_DIR}/frame/*.cpp")

source_group("frame" FILES ${FRAME_HPP} ${FRAME_CPP})

add_executable(server ${SOURCE_FILES})