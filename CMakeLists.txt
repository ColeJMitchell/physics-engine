cmake_minimum_required(VERSION 3.10)
project(physics-engine)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
find_package(glfw3 REQUIRED)
find_package(GLEW REQUIRED)

add_executable(
    world 
    src/main.cpp
)

target_include_directories(
    world
    PRIVATE
        include
)

target_link_libraries(
    world
    PRIVATE
        OpenGL::GL
        glfw
        GLEW::GLEW
)
