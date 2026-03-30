cmake_minimum_required(VERSION 3.10)
project(pingpong)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(raylib REQUIRED)
add_executable(pingpong main.cpp)
target_link_libraries(pingpong PRIVATE raylib)
