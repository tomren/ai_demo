cmake_minimum_required(VERSION 2.8)
project(server)

set (CMAKE_CXX_STANDARD 11)

# 添加 c++11 编译选项
if(CMAKE_COMPILER_IS_GNUCXX)
    add_compile_options(-std=c++11)
    message(STATUS "optional:-std=c++11")
endif(CMAKE_COMPILER_IS_GNUCXX)

# INCLUDE PATH
include_directories(${PROJECT_SOURCE_DIR})
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

# AI
# ============================================================
file(GLOB AI_SRC "${PROJECT_SOURCE_DIR}/ai/*.hpp" "${PROJECT_SOURCE_DIR}/ai/*.cpp")
file(GLOB AI_BT_SRC "${PROJECT_SOURCE_DIR}/ai/bt/*.hpp" "${PROJECT_SOURCE_DIR}/ai/bt/*.cpp")
file(GLOB AI_FSM_SRC "${PROJECT_SOURCE_DIR}/ai/fsm/*.hpp" "${PROJECT_SOURCE_DIR}/ai/fsm/*.cpp")

# UTIL
# ============================================================
file(GLOB UTIL_SRC "${PROJECT_SOURCE_DIR}/util/*.hpp" "${PROJECT_SOURCE_DIR}/util/*.cpp")

# NET
# ============================================================
file(GLOB NET_SRC "${PROJECT_SOURCE_DIR}/net/*.hpp" "${PROJECT_SOURCE_DIR}/net/*.cpp")

# CREATURE
# ============================================================
file(GLOB CREATURE_SRC "${PROJECT_SOURCE_DIR}/creature/*.hpp" "${PROJECT_SOURCE_DIR}/creature/*.cpp")

# FRAME
# ============================================================
file(GLOB FRAME_SRC "${PROJECT_SOURCE_DIR}/frame/*.hpp" "${PROJECT_SOURCE_DIR}/frame/*.cpp")

set(SOURCE_FILES main.cpp globals.hpp 
                 ${AI_SRC} 
                 ${AI_BT_SRC} 
                 ${AI_FSM_SRC} 
                 ${UTIL_SRC} 
                 ${NET_SRC} 
                 ${CREATURE_SRC} 
                 ${FRAME_SRC} )

source_group("frame" FILES ${FRAME_SRC})

add_executable(server ${SOURCE_FILES})