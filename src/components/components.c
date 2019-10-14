#include "components.h"

void CrummyComponentsImport(ecs_world_t * world, int flags)
{
    // Declare modules
    ECS_MODULE(world, CrummyComponents);

    // Register components
    ECS_COMPONENT(world, Position);
    ECS_COMPONENT(world, Sprite);

    // Export handles to components
    ECS_SET_COMPONENT(Position);
    ECS_SET_COMPONENT(Sprite);
}