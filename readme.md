# Crummy
Crummy is a particle physics simulator created with flecs and raylib. This project started out with my crummy attitude regarding object oriented programming.

<p align="center"><img src="https://github.com/alexjodonnell/crummy/blob/master/docs/paradise.gif" width="335" height="229" /></p>

## Goals
The goal of this project is to experiment with data driven programming for game development.

## To build 
- Make folders called lib and build in the project root
    - `mkdir lib build`
- Dependencies are built from source. Probably going to change this later on because it can be quite a pain.
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