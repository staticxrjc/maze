cmake_minimum_required(VERSION 3.16)
project(template VERSION 1.0.0)
add_subdirectory(inc)
add_subdirectory(src)
include_directories(inc)

add_executable(${PROJECT_NAME} src/main.cpp)

add_library(
    template
    src/template.cpp
    inc/template.h
)

target_link_libraries(${PROJECT_NAME} PRIVATE template)
