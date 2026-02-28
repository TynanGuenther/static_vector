cmake_minimum_required(VERSION 3.16)

project(StaticVectorProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(static_vector
    src/main.cpp
)

target_include_directories(static_vector PRIVATE include)
