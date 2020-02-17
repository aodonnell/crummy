#ifndef _CORE_H
#define _CORE_H

#include <stdint.h>

#include <raylib.h>
#include <flecs.h>

#include "handling.h"
#include "colors.h"

#define ROOT2OVER2 0.7071

typedef struct Camera2D Camera2D;

typedef struct Vector2 Position;

typedef struct Vector2 Velocity;

typedef enum _crumb_flavor
{
    VoidCrumb,
    RockCrumb,
    SandCrumb,
    WaterCrumb,
    PlantCrumb,
    LoudCrumb,
} CrumbFlavor;

typedef struct _crumb
{
    CrumbFlavor flavor;
} Crumb;

typedef struct _crumb_neighbor_set
{
    ecs_entity_t n;
    ecs_entity_t ne;
    ecs_entity_t e;
    ecs_entity_t se;
    ecs_entity_t s;
    ecs_entity_t sw;
    ecs_entity_t w;
    ecs_entity_t nw;
} CrumbNeighborSet;

extern Color CrumbColorLookup[];

#endif