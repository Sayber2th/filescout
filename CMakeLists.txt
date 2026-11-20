cmake_minimum_required(VERSION 4.2)
project(filescout CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(filescout)
target_sources(filescout PRIVATE main.cpp)