cmake_minimum_required(VERSION 3.15)

project(4_ACTIVITIES)

set(PROJECT_SOURCE
        activity.h
        activity.cpp
        activities.h
        activities.cpp
        activities_test.cpp
        main.cpp
        )

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-Wall -Wextra -Werror")
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_FLAGS_RELEASE "-O2")

add_executable(4_ACTIVITIES
        ${PROJECT_SOURCE}
        )