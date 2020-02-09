#include <flecs.h>

#include "chunk.h"
#include "crummy.h"

Vector4 world_to_chunk_position(Vector2 worldPosition)
{
    // <---> crumbs
    //  _________
    // |c00 |c01 |
    // |____|____|
    // |c10 |c11 |
    // |____|____|
    // <---------> pixels

    Vector2 chunkIndex = chunk_at(worldPosition);

    Vector4 chunkPosition = (Vector4){
        .x = chunkIndex.x,
        .y = chunkIndex.y,
        .z = ((int)worldPosition.x % CHUNK_SIZE_PX) / CRUMB_SIZE,
        .w = ((int)worldPosition.y % CHUNK_SIZE_PX) / CRUMB_SIZE};
}

Vector2 chunk_at(Vector2 worldPosition)
{
    worldPosition.x = worldPosition.x / CHUNK_SIZE_PX;
    worldPosition.y = worldPosition.y / CHUNK_SIZE_PX;
    return worldPosition;
}

bool chunk_exists()
{
}

ecs_entity_t GenOrReadChunk(ecs_world_t *world, Vector2 position)
{
}

ecs_entity_t ReadChunk(Vector2 chunkPosition)
{
}

ecs_entity_t GenChunk()
{
}

void WriteChunk(Chunk chunk)
{
}