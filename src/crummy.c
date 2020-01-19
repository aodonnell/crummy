#include "flecs.h"
#include "raylib.h"

#include "crummy.h"


#include "colours.h"
#include "entities/entities.h"
#include "components/components.h"
#include "systems/systems.h"

int main(int argc, char *argv[])
{
    InitWindow(WORLD_WIDTH, WORLD_HEIGHT, "crummy");

    ecs_world_t *world = ecs_init();

    ECS_IMPORT(world, CrummyComponents, 0);
    ECS_IMPORT(world, CrummySystems, 0);

    SpawnPlayableCrumb(world, (Vector2){100, 100});
    SpawnPlayableCrumb(world, (Vector2){200, 200});
    SpawnPlayableCrumb(world, (Vector2){300, 300});
    SpawnCrumb(world, (Vector2){400, 400});

    ecs_set_target_fps(world, 60);

    while (!WindowShouldClose() && ecs_progress(world, 0))
    {
        BeginDrawing();
        ClearBackground(DUSK);
        EndDrawing();
    }

    ecs_fini(world);

    return 0;
}