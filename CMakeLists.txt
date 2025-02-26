cmake_minimum_required(VERSION 3.10)
project(FileManager)

set(CMAKE_CXX_STANDARD 17)

add_executable(FileManager src/main.cpp src/FileManager.cpp)

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_LESS 9.1)
    target_link_libraries(FileManager stdc++fs)
endif()
