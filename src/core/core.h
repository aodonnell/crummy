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
    int n;
    int ne;
    int e;
    int se;
    int s;
    int sw;
    int w;
    int nw;
} CrumbNeighborSet;

extern Color CrumbColorLookup[];

#endif