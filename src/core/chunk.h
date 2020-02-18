#ifndef _Chunk_H
#define _Chunk_H

#include <raylib.h>

#include "core.h"
#include "crummy.h"

typedef struct _chunk
{
    Vector2 corner;
    int *crumbData;
    Color color;
    int id;
} Chunk;

// Vector4 world_to_chunk_position(Vector2 worldPosition);

void wipe_chunk(Chunk *chunk);

void chunk_monitor(Chunk *chunk);

int get_crumb_on_chunk(Chunk *chunk, Vector2 position);

void set_crumb_on_chunk(Chunk *chunk, Vector2 position, int crumbEntity);

CrumbNeighborSet get_crumb_neighbor_set(Chunk *chunk, Vector2 position);

ecs_entity_t chunk_at(Vector2 worldPosition);

void handle_chunk_click(ecs_rows_t *rows, ecs_entity_t chunkEntity, Chunk *chunkComponent, Vector2 worldPosition);

#endif