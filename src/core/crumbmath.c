#include <stdint.h>
#include <stdlib.h>

#include "crumbmath.h"

#include "crummy.h"

int snap_to_crumb_x(float snapX)
{
    return snapX / CRUMB_SIZE;
}

int snap_to_crumb_y(float snapY)
{
    return snapY / CRUMB_SIZE;
}

Vector2 snap_to_crumb(Vector2 snap)
{
    snap.x = snap_to_crumb_x(snap.x);
    snap.y = snap_to_crumb_y(snap.y);

    return snap;
}

int world_to_snap_x(float worldX)
{
    float crumbSize = CRUMB_SIZE;

    return (int)(worldX - (int)worldX % (int)(crumbSize));
}

int world_to_snap_y(float worldY)
{
    float crumbSize = CRUMB_SIZE;

    return (int)(worldY - (int)worldY % (int)(crumbSize));
}

Vector2 world_to_snap(Vector2 world)
{
    world.x = world_to_snap_x(world.x);
    world.y = world_to_snap_y(world.y);

    return world;
}

float screen_to_world_x(float screenX)
{
    return (screenX - camera.target.x - camera.offset.x) / camera.zoom + camera.target.x;
}

float screen_to_world_y(float screenY)
{
    return (screenY - camera.target.y - camera.offset.y) / camera.zoom + camera.target.y;
}

Vector2 screen_to_world(Vector2 screen)
{
    screen.x = screen_to_world_x(screen.x);
    screen.y = screen_to_world_y(screen.y);

    return screen;
}

float world_to_screen_x(float worldX)
{
    return (worldX - camera.target.x) * camera.zoom + camera.target.x + camera.offset.x;
}

float world_to_screen_y(float worldY)
{
    return (worldY - camera.target.y) * camera.zoom + camera.target.y + camera.offset.y;
}

Vector2 world_to_screen(Vector2 world)
{
    world.x = world_to_screen_x(world.x);
    world.y = world_to_screen_y(world.y);

    return world;
}

float world_to_chunk_x(float worldX)
{
    // return (int)(worldX - (int)worldX % (int)(CHUNK_SIZE))/;
    return world_to_snap_x(worldX) / (CHUNK_SIZE * CRUMB_SIZE);
}

float world_to_chunk_y(float worldY)
{

    // return (int)(worldY - (int)worldY % (int)(CHUNK_SIZE))/;
    return world_to_snap_y(worldY) / (CHUNK_SIZE * CRUMB_SIZE);
}

Vector2 world_to_chunk(Vector2 world)
{
    world.x = world_to_chunk_x(world.x);
    world.y = world_to_chunk_y(world.y);

    return world;
}

float screen_to_snap_x(float screenX)
{
    return world_to_snap_x(screen_to_world_x(screenX));
}

float screen_to_snap_y(float screenY)
{
    return world_to_snap_y(screen_to_world_y(screenY));
}

Vector2 screen_to_snap(Vector2 screen)
{
    screen.x = screen_to_snap_x(screen.x);
    screen.y = screen_to_snap_y(screen.y);

    return screen;
}

int rand_in_range(int low, int high)
{
    return (rand() % (high - low + 1)) + low;
}

double rand01()
{
    return rand() / (double)RAND_MAX;
}
