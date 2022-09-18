cmake_minimum_required(VERSION 3.15)

project(2_COUNT_SORT)

set(PROJECT_SOURCE
        ../catch.hpp
        count_sort.h
        count_sort.cpp
        count_sort_test.cpp
        main.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_executable(2_COUNT_SORT
        ${PROJECT_SOURCE})