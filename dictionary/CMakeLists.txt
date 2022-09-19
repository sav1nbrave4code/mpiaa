cmake_minimum_required(VERSION 3.15)

project(2_DICTIONARY)

set(PROJECT_SOURCE
        ../catch.hpp
        random_string.h
        random_string.cpp
        dictionary.h
        dictionary.cpp
        dictionary_test.cpp
        main.cpp)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_executable(2_DICTIONARY
        ${PROJECT_SOURCE})