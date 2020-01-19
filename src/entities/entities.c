#include "entities.h"
#include "components.h"
#include "systems.h"

ecs_entity_t SpawnCrumb(ecs_world_t *world)
{
    ecs_entity_t id = ecs_new(world, 0);

    ECS_IMPORT(world, CrummyComponents, 0);

    ecs_set(world, id, Position, {.x = 400, .y = 225});
    ecs_set(world, id, Velocity, {.x = 0, .y = 0});

    ecs_add(world, id, Crumb);
    ecs_add(world, id, Playable);

    return id;
}