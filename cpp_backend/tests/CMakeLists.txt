cmake_minimum_required(VERSION 3.12)

find_package(GTest)
find_package(Threads)

project(test_gol)

include_directories(${GTEST_INCLUDE_DIRS})

set(CMAKE_CXX_STANDARD 14)

add_executable(test_gol gol_test.cpp)
target_link_libraries(test_gol ${GTEST_BOTH_LIBRARIES} Threads::Threads)