cmake_minimum_required(VERSION 3.15)

project(3_CLOSEST_PAIR)

set(PROJECT_SOURCE
        ../catch.hpp
        point.h
        point.cpp
        point_test.cpp
        closest_pair.h
        closest_pair.cpp
        closest_pair_test.cpp
        main.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_executable(3_CLOSEST_PAIR
        ${PROJECT_SOURCE})