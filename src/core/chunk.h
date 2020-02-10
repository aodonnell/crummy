#ifndef _Chunk_H
#define _Chunk_H

#include <raylib.h>

#include "core.h"
#include "crummy.h"

typedef struct _chunk
{
    Vector2 corner;
    Crumb *crumbData;
} Chunk;

// Vector4 world_to_chunk_position(Vector2 worldPosition);

ecs_entity_t chunk_at(Vector2 worldPosition);

void handle_chunk_click(ecs_world_t *world, ecs_entity_t chunkEntity, Chunk *chunkComponent, Vector2 worldPosition);

#endif