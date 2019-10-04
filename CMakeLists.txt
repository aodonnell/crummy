cmake_minimum_required(VERSION 3.11)

project(crummy)

add_subdirectory(raylib/src)

add_executable(${PROJECT_NAME} src/main.c)

target_link_libraries(${PROJECT_NAME} raylib)