#include "entities.h"
#include "components.h"

ecs_entity_t SpawnCowboy(ecs_world_t * world)
{
    ecs_entity_t id = ecs_new(world, 0);
    
    Texture2D cowboi = LoadTexture("assets/cowboy.png");

    ECS_IMPORT(world, CrummyComponents, 0);

    ecs_set(world, id, Sprite, {.texture = cowboi});
    ecs_set(world, id, Position, {.x = 400, .y = 225});

    return id;
}