cmake_minimum_required(VERSION 3.21)
project(maze VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set (CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
add_subdirectory(src)
add_subdirectory(sdk/SFML)
include_directories(inc)
include_directories(sdk/SFML/include)

add_executable(${PROJECT_NAME} src/main.cpp)

add_library(
    engine STATIC
    src/engine.cpp
    inc/engine.h
)

target_link_libraries(${PROJECT_NAME} 
    engine
    sfml-system
    sfml-window
    sfml-graphics
    sfml-network
    sfml-audio)
