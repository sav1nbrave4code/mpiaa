cmake_minimum_required(VERSION 3.15)

project(TSP_6)

set(PROJECT_SOURCE
        graph.h
        graph.cpp
        tsp.h
        tsp.cpp
        tsp_test.cpp
        main.cpp
        ../catch.hpp)

add_executable(TSP_6
        ${PROJECT_SOURCE})