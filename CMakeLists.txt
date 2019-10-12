cmake_minimum_required(VERSION 3.11)

project(crummy)

add_subdirectory(raylib/src)

add_executable(${PROJECT_NAME} src/crummy.c)

file(COPY assets DESTINATION .)

target_link_libraries(${PROJECT_NAME} raylib)