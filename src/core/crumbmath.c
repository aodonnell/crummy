#include <stdint.h>
#include <stdlib.h>

#include "crumbmath.h"

#include "crummy.h"

int SnapToCrumbX(float snapX)
{
    return snapX / CRUMB_SIZE;
}

int SnapToCrumbY(float snapY)
{
    return snapY / CRUMB_SIZE;
}

Vector2 SnapToCrumb(Vector2 snap)
{
    snap.x = SnapToCrumbX(snap.x);
    snap.y = SnapToCrumbY(snap.y);

    return snap;
}

int WorldToSnapX(float worldX)
{
    float crumbSize = CRUMB_SIZE;

    return (int)(worldX - (int)worldX % (int)(crumbSize));
}

int WorldToSnapY(float worldY)
{
    float crumbSize = CRUMB_SIZE;

    return (int)(worldY - (int)worldY % (int)(crumbSize));
}

Vector2 WorldToSnap(Vector2 world)
{
    world.x = WorldToSnapX(world.x);
    world.y = WorldToSnapY(world.y);

    return world;
}

float ScreenToWorldX(float screenX)
{
    return (screenX - camera.target.x - camera.offset.x) / camera.zoom + camera.target.x;
}

float ScreenToWorldY(float screenY)
{
    return (screenY - camera.target.y - camera.offset.y) / camera.zoom + camera.target.y;
}

Vector2 ScreenToWorld(Vector2 screen)
{
    screen.x = ScreenToWorldX(screen.x);
    screen.y = ScreenToWorldY(screen.y);

    return screen;
}

float WorldToScreenX(float worldX)
{
    return (worldX - camera.target.x) * camera.zoom + camera.target.x + camera.offset.x;
}

float WorldToScreenY(float worldY)
{
    return (worldY - camera.target.y) * camera.zoom + camera.target.y + camera.offset.y;
}

Vector2 WorldToScreen(Vector2 world)
{
    world.x = WorldToScreenX(world.x);
    world.y = WorldToScreenY(world.y);

    return world;
}

float ScreenToSnapX(float screenX)
{
    return WorldToSnapX(ScreenToWorldX(screenX));
}

float ScreenToSnapY(float screenY)
{
    return WorldToSnapY(ScreenToWorldY(screenY));
}

Vector2 ScreenToSnap(Vector2 screen)
{
    screen.x = ScreenToSnapX(screen.x);
    screen.y = ScreenToSnapY(screen.y);

    return screen;
}

int RandInRange(int low, int high)
{
    return (rand() % (high - low + 1)) + low;
}

double Rand01()
{
    return rand() / (double)RAND_MAX;
}
