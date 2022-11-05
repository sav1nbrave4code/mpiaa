cmake_minimum_required(VERSION 3.15)

project(5_MIN_SPANNING_TREE)

set(PROJECT_SOURCE
        ../catch.hpp
        graph.h
        graph.cpp
        min_spanning_tree.h
        min_spanning_tree.cpp
        min_spanning_tree_test.cpp
        main.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_executable(5_MIN_SPANNING_TREE
        ${PROJECT_SOURCE})