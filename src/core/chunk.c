#include <flecs.h>

#include "chunk.h"
#include "crummy.h"
#include "crumbmath.h"

#include "entities.h"
#include "components.h"

Vector4 world_to_chunk_position(Vector2 worldPosition)
{
    // <---> crumbs
    //  _________
    // |c00 |c01 |
    // |____|____|
    // |c10 |c11 |
    // |____|____|
    // <---------> pixels

    // Vector2 chunkIndex = chunk_at(worldPosition);

    // Vector4 chunkPosition = (Vector4){
    //     .x = chunkIndex.x,
    //     .y = chunkIndex.y,
    //     .z = ((int)worldPosition.x % CHUNK_SIZE_PX) / CRUMB_SIZE,
    //     .w = ((int)worldPosition.y % CHUNK_SIZE_PX) / CRUMB_SIZE};
}

ecs_entity_t chunk_at(Vector2 worldPosition)
{
    return the_lone_chunk;
}

bool chunk_exists()
{
}

ecs_entity_t gen_or_read_chunk(ecs_world_t *world, Vector2 position)
{
}

ecs_entity_t read_chunk(Vector2 chunkPosition)
{
}

ecs_entity_t gen_chunk(Vector2 chunkPosition)
{
}

void write_chunk(Chunk chunk)
{
}

void handle_chunk_click(ecs_world_t *world, ecs_entity_t chunkEntity, Chunk *chunkComponent, Vector2 worldPosition)
{
    // check to see if the worldPosition falls inside the chunk.

    Vector2 chunkPosition = world_to_chunk(worldPosition);

    bool sameChunk = (chunkPosition.x == chunkComponent->corner.x && chunkPosition.y == chunkComponent->corner.y);

    if (sameChunk)
    {
        spawn_crumb(world, chunkEntity, world_to_snap(worldPosition), LoudCrumb);
    }
}