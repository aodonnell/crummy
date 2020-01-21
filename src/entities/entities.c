
#include "colors.h"
#include "core.h"
#include "entities.h"
#include "components.h"
#include "systems.h"

ecs_entity_t SpawnCrumb(ecs_world_t *world, Vector2 position, CrumbFlavor type)
{
    ecs_entity_t id = ecs_new(world, 0);

    ECS_IMPORT(world, CrummyComponents, 0);

    ecs_set(world, id, Position, {.x = position.x, .y = position.y});
    ecs_set(world, id, Velocity, {.x = 0, .y = 0});

    ecs_set(world, id, Crumb, {.type = type});

    return id;
}