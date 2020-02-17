#include <flecs.h>

#include "chunk.h"
#include "crummy.h"
#include "crumbmath.h"

#include "entities.h"
#include "components.h"

void wipe_chunk(Chunk *chunk)
{
    memset(chunk->crumbData, -1, CHUNK_SIZE * CHUNK_SIZE * sizeof(int));
}

void chunk_monitor(Chunk *chunk)
{
    printf("=============================\n");
    for (int i = 0; i < CHUNK_SIZE; ++i)
    {
        for (int j = 0; j < CHUNK_SIZE; ++j)
        {
            printf("%4.d ", get_crumb_on_chunk(chunk, (Vector2){.x = j, .y = i}));
        }
        puts("");
    }
    printf("=============================\n");
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

int get_crumb_on_chunk(Chunk *chunk, Vector2 position)
{
    return chunk->crumbData[crumb_index_from_position(position)];
}

void set_crumb_on_chunk(Chunk *chunk, Vector2 position, ecs_entity_t crumbEntity)
{
    chunk->crumbData[crumb_index_from_position(position)] = (int)crumbEntity;
}

CrumbNeighborSet get_crumb_neighbor_set(Chunk *chunk, Vector2 position)
{
    CrumbNeighborSet set;

    set.n = get_crumb_on_chunk(chunk, (Vector2){.x = position.x, .y = position.y - 1});
    set.ne = get_crumb_on_chunk(chunk, (Vector2){.x = position.x + 1, .y = position.y - 1});
    set.e = get_crumb_on_chunk(chunk, (Vector2){.x = position.x + 1, .y = position.y});
    set.se = get_crumb_on_chunk(chunk, (Vector2){.x = position.x + 1, .y = position.y + 1});
    set.s = get_crumb_on_chunk(chunk, (Vector2){.x = position.x, .y = position.y + 1});
    set.sw = get_crumb_on_chunk(chunk, (Vector2){.x = position.x - 1, .y = position.y + 1});
    set.w = get_crumb_on_chunk(chunk, (Vector2){.x = position.x - 1, .y = position.y});
    set.nw = get_crumb_on_chunk(chunk, (Vector2){.x = position.x - 1, .y = position.y - 1});

    return set;
};

void handle_chunk_click(ecs_rows_t *rows, ecs_entity_t chunkEntity, Chunk *chunkComponent, Vector2 worldPosition)
{
    Vector4 chunkPosition = world_to_chunk_and_crumb(worldPosition);

    bool sameChunk = (chunkPosition.x == chunkComponent->corner.x && chunkPosition.y == chunkComponent->corner.y);

    if (sameChunk)
    {
        // if there's already a crumb here, alter its properties
        int hitCrumbEntity = get_crumb_on_chunk(chunkComponent, (Vector2){.x = chunkPosition.z, .y = chunkPosition.w});

        if (hitCrumbEntity >= 0)
        {
            ECS_COLUMN_COMPONENT(rows, Crumb, 1);

            Crumb *crumb = rows->columns;

            if (crumb != NULL)
            {
                crumb->flavor = WaterCrumb;
            }
        }
        else
        {
            int crumbid = spawn_crumb(rows->world, chunkEntity, world_to_snap(worldPosition), selectedFlavor);

            set_crumb_on_chunk(chunkComponent, (Vector2){.x = chunkPosition.z, .y = chunkPosition.w}, crumbid);
        }
    }
}