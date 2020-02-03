cmake_minimum_required(VERSION 3.11)

project(crummy)

include_directories(lib/flecs/include)
include_directories(lib/unqlite/src)
include_directories(lib/raylib/src)

include_directories(src)
include_directories(src/core)
include_directories(src/entities)
include_directories(src/components)
include_directories(src/systems)

file(GLOB SOURCES src/*.c src/entities/*.c src/components/*.c src/systems/*.c src/core/*.c)

add_executable(${PROJECT_NAME} src/crummy.c ${SOURCES})

file(COPY assets DESTINATION .)

find_library(RAYLIB raylib lib/raylib/build)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${RAYLIB})

find_library(FLECS flecs_static lib/flecs/build)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${FLECS})

find_library(UNQLITE unqlite lib/unqlite/build)
target_link_libraries(${PROJECT_NAME} LINK_PUBLIC ${UNQLITE})