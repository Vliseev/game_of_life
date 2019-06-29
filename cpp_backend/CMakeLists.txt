cmake_minimum_required(VERSION 3.12)

project(cpp_backend)


set(CMAKE_CXX_STANDARD 14)
add_subdirectory(tests)
add_executable(cpp_backend main.cpp)