cmake_minimum_required(VERSION 3.8)

project(Hikachi VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main "main.cpp" "main.h" "shader.cpp" "shader.h")