cmake_minimum_required(VERSION 3.15)

project(1_CONTAINERS)

set(PROJECT_SOURCE
        ../catch.hpp
        main.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_executable(1_CONTAINERS
               ${PROJECT_SOURCE})
