cmake_minimum_required(VERSION 3.10)
project(physics-engine)

set(CMAKE_CXX_STANDARD 17)

find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)

# GLFW
find_package(glfw3 REQUIRED)

# GLEW
find_package(GLEW REQUIRED)

add_executable(myapp main.cpp)

target_link_libraries(myapp
    PRIVATE
    OpenGL::GL
    glfw
    GLEW::GLEW
)
