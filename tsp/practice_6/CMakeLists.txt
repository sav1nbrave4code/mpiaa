cmake_minimum_required(VERSION 3.15)

project(TSP_6)

set(PROJECT_SOURCE
        graph.h
        graph.cpp
        tsp.h
        tsp.cpp
        tsp_test.cpp
        main.cpp
        ../../catch.hpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_executable(TSP_6
        ${PROJECT_SOURCE})