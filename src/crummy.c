#include "flecs.h"
#include "raylib.h"

#include "crummy.h"

#include "entities/entities.h"
#include "components/components.h"
#include "systems/systems.h"

const int screenWidth = 800;
const int screenHeight = 450;

int main(int argc, char* argv[])
{
    InitWindow(screenWidth, screenHeight, "crummy");

    Texture2D cowboi = LoadTexture("assets/cowboy.png");

    ecs_world_t * world = ecs_init();

    ECS_IMPORT(world, CrummyComponents, 0);
    ECS_IMPORT(world, CrummySystems, 0);

    SpawnCowboy(world);

    ecs_set_target_fps(world, 1);
    
    while(!WindowShouldClose() && ecs_progress(world, 0))
    {
        // game loop stuff
    }

    ecs_fini(world);
    
    return 0;
}