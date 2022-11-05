cmake_minimum_required(VERSION 3.15)

project(5_SHORTEST_PATH)

set(PROJECT_SOURCE
        ../catch.hpp
        graph.h
        graph.cpp
        graph_test.cpp
        shortest_path.h
        shortest_path.cpp
        shortest_path_test.cpp
        main.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_executable(5_SHORTEST_PATH
        ${PROJECT_SOURCE})