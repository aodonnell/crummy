cmake_minimum_required(VERSION 3.11)

project(crummy)

find_package(raylib 2.0 QUIET)

if (NOT raylib_FOUND)
    include(FetchContent)

    FetchContent_Declare(
    raylib
    URL https://github.com/raysan5/raylib/archive/master.tar.gz
    )

    FetchContent_GetProperties(raylib)
    if (NOT raylib_POPULATED) # Have we downloaded raylib yet?
    set(FETCHCONTENT_QUIET NO)
    FetchContent_Populate(raylib)

    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

    # build raylib
    add_subdirectory(${raylib_SOURCE_DIR} ${raylib_BINARY_DIR})

    endif()
endif()

add_executable(${PROJECT_NAME} src/main.c)

target_link_libraries(${PROJECT_NAME} raylib)