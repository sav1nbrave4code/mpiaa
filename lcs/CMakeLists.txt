cmake_minimum_required(VERSION 3.15)

project(4_LCS)

set(PROJECT_SOURCE
        lcs.h
        lcs.cpp
        lcs_test.cpp
        main.cpp
        )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_executable(4_LCS
        ${PROJECT_SOURCE}
        )