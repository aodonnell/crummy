#include <flecs.h>
#include <raylib.h>
#include <sys/time.h>

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

    Camera2D camera = {.target = (Vector2){WINDOW_WIDTH_PX, WINDOW_HEIGHT_PX},
                       .offset = (Vector2){0, 0},
                       .rotation = 0.0f,
                       .zoom = 1.0f};

    // SpawnCrumb(world, (Vector2){0, 512}, RockCrumb);
    SpawnCamera2D(world, (Vector2){0, 512}, &camera);

    ecs_set_target_fps(world, 60);


    struct timeval ti, tf;
    double deltat;

    while (!WindowShouldClose() && ecs_progress(world, deltat))
    {
        gettimeofday(&ti, NULL);
        BeginDrawing();
        ClearBackground(DUSK);
        EndDrawing();
        gettimeofday(&tf, NULL);

        deltat = (tf.tv_sec - ti.tv_sec) * 1000.0;      // sec to ms
        deltat += (tf.tv_usec - ti.tv_usec) / 1000.0;   // us to ms
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