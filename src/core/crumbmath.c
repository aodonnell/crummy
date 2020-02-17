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

int world_to_crumb_x(float worldX)
{
    return snap_to_crumb_x(world_to_snap_x(worldX));
}

int world_to_crumb_y(float worldY)
{
    return snap_to_crumb_y(world_to_snap_y(worldY));
}

Vector2 world_to_crumb(Vector2 world)
{
    world.x = world_to_crumb_x(world.x);
    world.y = world_to_crumb_y(world.y);

    return world;
}

int world_to_snap_x(float worldX)
{
    return (int)(worldX - (int)worldX % (int)(CRUMB_SIZE)) - CRUMB_SIZE * (worldX < 0 ? 1 : 0);
}

int world_to_snap_y(float worldY)
{
    return (int)(worldY - (int)worldY % (int)(CRUMB_SIZE)) - CRUMB_SIZE * (worldY < 0 ? 1 : 0);
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
    return (int)(worldX - (int)worldX % (int)(CRUMB_SIZE)) / (CHUNK_SIZE_PX) - (worldX < 0 ? 1 : 0);
}

float world_to_chunk_y(float worldY)
{
    return (int)(worldY - (int)worldY % (int)(CRUMB_SIZE)) / (CHUNK_SIZE_PX) - (worldY < 0 ? 1 : 0);
}

Vector2 world_to_chunk(Vector2 world)
{
    world.x = world_to_chunk_x(world.x);
    world.y = world_to_chunk_y(world.y);

    return world;
}

float chunk_to_world_x(float chunkX)
{
    return chunkX * CHUNK_SIZE_PX;
}

float chunk_to_world_y(float chunkY)
{
    return chunkY * CHUNK_SIZE_PX;
}

Vector2 chunk_to_world(Vector2 chunk)
{
    chunk.x = chunk_to_world_x(chunk.x);
    chunk.y = chunk_to_world_y(chunk.y);

    return chunk;
}

Vector4 world_to_chunk_and_crumb(Vector2 world)
{
    // <---> crumbs
    //  _________
    // |c00 |c01 |
    // |____|____|
    // |c10 |c11 |
    // |____|____|
    // <---------> pixels

    int x, y, z, w;

    x = world_to_chunk_x(world.x);
    y = world_to_chunk_y(world.y);
    z = world_to_crumb_x(world.x - chunk_to_world_x(x));
    w = world_to_crumb_y(world.y - chunk_to_world_y(y));

    return (Vector4){.x = x, .y = y, .z = z, .w = w};
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

int crumb_index_from_position(Vector2 position)
{
    return ((int)position.y * CRUMB_SIZE + (int)position.x);
}

int rand_in_range(int low, int high)
{
    return (rand() % (high - low + 1)) + low;
}

double rand01()
{
    return rand() / (double)RAND_MAX;
}
