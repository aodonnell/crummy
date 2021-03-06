
#include "colors.h"
#include "core.h"
#include "entities.h"
#include "components.h"
#include "systems.h"

ecs_entity_t spawn_crumb(ecs_world_t *world, ecs_entity_t parentChunk, Vector2 position, CrumbFlavor flavor)
{
    ecs_entity_t id;

    id = ecs_new_child(world, parentChunk, 0);

    ECS_IMPORT(world, CrummyComponents, 0);

    ecs_set(world, id, Position, {.x = position.x, .y = position.y});
    ecs_set(world, id, Velocity, {.x = 0, .y = 0});
    ecs_set(world, id, Crumb, {.flavor = flavor});

    printf("boom\n");

    return id;
}

ecs_entity_t spawn_camera_2d(ecs_world_t *world, Vector2 position, Camera2D *camera)
{
    ecs_entity_t id = ecs_new(world, 0);

    ECS_IMPORT(world, CrummyComponents, 0);

    ecs_set(world, id, Velocity, {.x = 0, .y = 0});
    ecs_set(world, id, Position, {.x = position.x, .y = position.y});
    ecs_set_ptr(world, id, Camera2D, camera);

    ecs_add(world, id, Playable);

    return id;
}

ecs_entity_t spawn_chunk(ecs_world_t *world, Vector2 corner)
{
    ecs_entity_t id = ecs_new(world, 0);

    ECS_IMPORT(world, CrummyComponents, 0);

    int *data = malloc(CHUNK_SIZE * CHUNK_SIZE * sizeof(int));
    Chunk chunk = {.crumbData = data, .corner = corner, .color = rand_tint(), .id = id};

    wipe_chunk(&chunk);

    ecs_entity_t crumb = spawn_crumb(world, id, (Vector2){CRUMB_SIZE + CHUNK_SIZE_PX * corner.x, CRUMB_SIZE + CHUNK_SIZE_PX * corner.y}, RockCrumb);
    set_crumb_on_chunk(&chunk, (Vector2){.x = 1, .y = 1}, (int)crumb);

    ecs_set_ptr(world, id, Chunk, &chunk);

    return id;
}
