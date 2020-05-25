cmake_minimum_required(VERSION 3.16)
project(omicron)
set(CMAKE_CXX_STANDARD 14)

include_directories(./src)
file(GLOB Sources ./src/*.cpp ./src/*.hpp)
add_executable(omicron ${Sources})

target_link_libraries(omicron stdc++ "-framework Foundation" "-framework Cocoa" objc)