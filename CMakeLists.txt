cmake_minimum_required(VERSION 3.8)

project(Hikachi VERSION 1.0)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(main "src/main.cpp" "src/main.h" "src/shader.cpp" "src/shader.h" "src/glad.c")

target_include_directories(main PRIVATE "C:/Dev/include")
target_link_directories(main PRIVATE "C:/Dev/lib")

target_link_libraries(main glfw3 opengl32)
