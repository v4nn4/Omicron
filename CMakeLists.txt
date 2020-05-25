cmake_minimum_required(VERSION 3.16)
project(omicron)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(omicron
        coordinates.cpp
        coordinates.hpp
        main.cpp
        math.hpp
        polygon.cpp
        polygon.hpp
        quaternion.cpp
        quaternion.hpp
        vector3d.cpp
        vector3d.hpp)
