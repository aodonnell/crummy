#ifndef _CORE_H
#define _CORE_H

#include "handling.h"

#include "colors.h"
#include "raylib.h"

#include <stdint.h>

#define ROOT2OVER2 0.7071

typedef struct Vector2 Position;

typedef struct Vector2 Velocity;

typedef enum _crumb_type
{
    VoidCrumb,
    RockCrumb,
    SandCrumb,
    WaterCrumb,
    PlantCrumb,
} CrumbType;

typedef struct _crumb 
{
    CrumbType type;
} Crumb;

extern int Chunk[];

extern Color CrumbColorLookup[];

bool CrumbsHitting(Position crumba, Position crumbb);

int FloatToSnap(float pos);
Vector2 Vector2ToSnap(Vector2 pos);

int RandInRange(int low, int high);

Vector2 Vector2Lerp(Vector2 current, Vector2 target, float by);


// XXX temporary chunk methods
int CrumbAt(Vector2 position);

bool SetCrumb(Position position, int crumb);

Vector2 PixelToChunkPosition(Position position);

int ChunkIndexFromChunkPosition(Vector2 chunkPosition);

void WipeChunk();

#endif