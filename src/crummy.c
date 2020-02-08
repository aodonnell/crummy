#include <flecs.h>
#include <raylib.h>

#include "crummy.h"
#include "colors.h"
#include "core.h"
#include "db.h"

#include "entities.h"
#include "components.h"
#include "systems.h"

char *universe = "theuniverse.crummy";

void init();

int main(int argc, char *argv[])
{
    ecs_world_t *world = ecs_init();

    init();

    ECS_IMPORT(world, CrummyComponents, 0);
    ECS_IMPORT(world, CrummySystems, 0);

    Camera2D camera = {.target = (Vector2){0, 0},
                       .offset = (Vector2){0, 0},
                       .rotation = 0.0f,
                       .zoom = 1.0f};

    SpawnCrumb(world, (Vector2){0, 512}, RockCrumb);
    SpawnCamera2D(world, (Vector2){0, 512}, &camera);

    ecs_set_target_fps(world, 60);

    while (!WindowShouldClose() && ecs_progress(world, 0))
    {
        BeginDrawing();
        ClearBackground(DUSK);
        BeginMode2D(camera);
        EndDrawing();
    }

    ecs_fini(world);

    return 0;
}

void init()
{
    question_or_create_universe(universe);

    InitWindow(WINDOW_WIDTH_PX, WINDOW_HEIGHT_PX, "crummy");

    FontAlagard = LoadFont("assets/alagard.png");
}