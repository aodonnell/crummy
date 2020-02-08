#ifndef _CORE_H
#define _CORE_H

#include <stdint.h>

#include <raylib.h>

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
} CrumbFlavor;

typedef struct _crumb 
{
    CrumbFlavor flavor;
} Crumb;

extern Color CrumbColorLookup[];

int FloatToSnap(float pos);
Vector2 Vector2ToSnap(Vector2 pos);

int RandInRange(int low, int high);

Vector2 Vector2Lerp(Vector2 current, Vector2 target, float by);

double Rand01();

#endif