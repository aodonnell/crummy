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

    camera.target = (Vector2){WINDOW_WIDTH_PX / 2, WINDOW_HEIGHT_PX / 2};
    camera.offset = (Vector2){0, 0};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;

    spawn_crumb(world, 0, (Vector2){0, 512}, RockCrumb);

    the_lone_chunk = spawn_chunk(world, (Vector2){0, 0}, NULL);

    spawn_camera_2d(world, (Vector2){WINDOW_WIDTH_PX / 2, WINDOW_HEIGHT_PX / 2}, &camera);

    ecs_set_target_fps(world, 60);

    while (!WindowShouldClose() && ecs_progress(world, 0))
    {
        EndDrawing();
        ClearBackground(DUSK);
        BeginDrawing();
    }

    ecs_fini(world);

    return 0;
}

void init()
{
    question_or_create_universe(universe);

    InitWindow(WINDOW_WIDTH_PX, WINDOW_HEIGHT_PX, "crummy");

    ToggleFullscreen();

    FontAlagard = LoadFont("assets/alagard.png");
}