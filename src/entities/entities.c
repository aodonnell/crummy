
#include "colours.h"
#include "core.h"
#include "entities.h"
#include "components.h"
#include "systems.h"

ecs_entity_t SpawnCrumb(ecs_world_t *world, Vector2 position)
{
    ecs_entity_t id = ecs_new(world, 0);

    ECS_IMPORT(world, CrummyComponents, 0);

    ecs_set(world, id, Position, {.x = position.x, .y = position.y});
    ecs_set(world, id, Velocity, {.x = 0, .y = 0});

    Color rand = {RandInRange(0, 0xff), RandInRange(0, 0xff), RandInRange(0, 0xff), 0xff};

    ecs_set(world, id, Crumb, {.color = rand});

    ecs_add(world, id, Playable);

    return id;
}

ecs_entity_t SpawnPlayableCrumb(ecs_world_t *world, Vector2 position)
{
    ecs_entity_t id = SpawnCrumb(world, position);

    ECS_IMPORT(world, CrummyComponents, 0);

    ecs_set(world, id, Crumb, {.color= PRETTY_IN_PINK});

    ecs_add(world, id, Playable);

    return id;
}