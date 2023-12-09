cmake_minimum_required(VERSION 3.5)

project(path_optimization)

set(CMAKE_CXX_STANDAND 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS TRUE)

find_package(Boost COMPONENTS coroutine QUIET)
add_executable(${PROJECT_NAME} my_optimization.cpp)
