# Crummy
Crummy is a particle physics simulator created with flecs and raylib. 

## Goals
The goal of this project is to experiment with data driven paradigms for game development.

## To build 
- Make folders called lib and build in the project root
    - `mkdir lib build`
- Dependencies are built from source.
- Flecs is an excellent entity component system in
- To handle cross platform rendering and audio, raylib is used.
- Go to the lib directory and clone flecs and raylib from github
    - `cd lib`
    - `git clone https://github.com/SanderMertens/flecs`
    - `git clone https://github.com/raysan5/raylib`
- To build,
    - `cd build`
    - `camke ..`
    - `make`
- Finally, to run
    - `./crummy`