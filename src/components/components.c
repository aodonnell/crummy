#include "components.h"

void CrummyComponentsImport(ecs_world_t *world, int flags)
{
    // Declare modules
    ECS_MODULE(world, CrummyComponents);

    // Register components
    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Velocity);
    ECS_COMPONENT(world, Crumb);
    ECS_COMPONENT(world, Chunk);
    ECS_COMPONENT(world, Camera2D);

    // Register tags
    ECS_TAG(world, Playable);

    // Export handles to components
    ECS_SET_COMPONENT(Position);
    ECS_SET_COMPONENT(Velocity);
    ECS_SET_COMPONENT(Crumb);
    ECS_SET_COMPONENT(Chunk);
    ECS_SET_COMPONENT(Camera2D);
    ECS_SET_ENTITY(Playable);
}