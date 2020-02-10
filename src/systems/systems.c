#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "raylib.h"

#include "colors.h"
#include "crummy.h"
#include "crumbmath.h"

#include "core.h"

#include "systems.h"
#include "entities.h"
#include "components.h"

// xxx no type safety. (should make a better one)
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

void CrumbRenderer(ecs_rows_t *rows)
{
    Position *positions = ecs_column(rows, Position, 1);
    Crumb *crumbs = ecs_column(rows, Crumb, 2);

    Vector2 mousePosition = GetMousePosition();

    BeginMode2D(camera);

    for (int i = 0; i < rows->count; i++)
    {
        DrawRectangle(positions[i].x, positions[i].y, CRUMB_SIZE, CRUMB_SIZE, CrumbColorLookup[crumbs[i].flavor]);
    }

    EndMode2D();
}

void CrumbSimulator(ecs_rows_t *rows)
{
    Position *positions = ecs_column(rows, Position, 1);
    Velocity *velocities = ecs_column(rows, Velocity, 2);
    Crumb *crumbs = ecs_column(rows, Crumb, 3);

    int n, ne, e, se, s, sw, w, nw;

    int sewater = 0;
    int swwater = 0;
    int swater = 0;

    float baseSpeed = CRUMB_SIZE / 2;

    Vector2 targetV;

    for (int i = 0; i < rows->count; i++)
    {
        // s = CrumbAt((Position){.x = positions[i].x, .y = positions[i].y + CRUMB_SIZE});
        // w = CrumbAt((Position){.x = positions[i].x - CRUMB_SIZE, .y = positions[i].y});
        // e = CrumbAt((Position){.x = positions[i].x + CRUMB_SIZE, .y = positions[i].y});
        // sw = CrumbAt((Position){.x = positions[i].x - CRUMB_SIZE, .y = positions[i].y + CRUMB_SIZE});
        // se = CrumbAt((Position){.x = positions[i].x + CRUMB_SIZE, .y = positions[i].y + CRUMB_SIZE});

        switch (crumbs[i].flavor)
        {
        case VoidCrumb:
            // XXX delete the crumb if it was set to void?
            break;
        case SandCrumb:

            // sewater = (crumbs[se].flavor == WaterCrumb);
            // swwater = (crumbs[sw].flavor == WaterCrumb);
            // swater = (crumbs[s].flavor == WaterCrumb);

            // if((se >= 0 && (sewater))       \
                //     || (sw >= 0 && (swwater))   \
                //     || (s >= 0 && (swater)))    \
                // {

            //     crumbs[i].flavor = WaterCrumb;

            //     if(swater)
            //     {
            //         crumbs[s].flavor = SandCrumb;
            //     }
            //     else if((sewater && swwater && rand01() < 0.5) || (sewater && !swwater))
            //     {
            //         crumbs[se].flavor = SandCrumb;
            //     }
            //     else
            //     {
            //         crumbs[s].flavor = SandCrumb;
            //     }

            //     break;
            // }

            e = e < 0;
            w = w < 0;
            s = s < 0;

            se = se < 0 && e;
            sw = sw < 0 && w;

            if (s)
            {
                targetV.x = 0;
                targetV.y = baseSpeed;
            }
            else if ((sw && se && rand01() > 0.5) || (sw && !se))
            {
                targetV.x = -ROOT2OVER2 * baseSpeed;
                targetV.y = ROOT2OVER2 * baseSpeed;
            }
            else if (se)
            {
                targetV.x = ROOT2OVER2 * baseSpeed;
                targetV.y = ROOT2OVER2 * baseSpeed;
            }
            else
            {
                targetV.x = 0;
                targetV.y = 0;
            }

            velocities[i] = Vector2Lerp(velocities[i], targetV, 0.5);
            break;

        case WaterCrumb:

            if ((se >= 0 && crumbs[se].flavor == PlantCrumb) || (sw >= 0 && crumbs[sw].flavor == PlantCrumb) || (s >= 0 && crumbs[s].flavor == PlantCrumb))
            {
                if (rand01() < DANK_FACTOR)
                {
                    crumbs[i].flavor = PlantCrumb;
                    velocities[i].x = 0;
                    velocities[i].y = 0;
                }
                break;
            }

            e = e < 0;
            w = w < 0;
            s = s < 0;

            se = se < 0 && e;
            sw = sw < 0 && w;

            if (s)
            {
                targetV.x = 0;
                targetV.y = baseSpeed;
            }
            else if ((sw && se && rand01() > 0.5) || (sw && !se))
            {
                targetV.x = -ROOT2OVER2 * baseSpeed;
                targetV.y = ROOT2OVER2 * baseSpeed;
            }
            else if (se)
            {
                targetV.x = ROOT2OVER2 * baseSpeed;
                targetV.y = ROOT2OVER2 * baseSpeed;
            }
            else if ((e && w && rand01() > 0.5) || (e && !w))
            {
                targetV.x = baseSpeed;
                targetV.y = 0;
            }
            else if (w)
            {
                targetV.x = -baseSpeed;
                targetV.y = 0;
            }
            else
            {
                targetV.x = 0;
                targetV.y = 0;
            }

            velocities[i] = Vector2Lerp(velocities[i], targetV, 0.5);

            break;

        default:
            break;
        }
    }
}

void MouseCrumber(ecs_rows_t *rows)
{
    // Position *positions = ecs_column(rows, Position, 1);
    // Crumb *crumbs = ecs_column(rows, Crumb, 2);

    Chunk *chunks = ecs_column(rows, Chunk, 1);

    bool rightDown = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
    bool leftDown = IsMouseButtonDown(MOUSE_LEFT_BUTTON);

    CrumbFlavor crumbType = VoidCrumb;

    if (rightDown && !leftDown)
    {
        if (IsKeyDown(KEY_SPACE))
        {
            crumbType = WaterCrumb;
        }
        else
        {
            crumbType = SandCrumb;
        }
    }
    else if (!rightDown && leftDown)
    {
        if (IsKeyDown(KEY_SPACE))
        {
            crumbType = RockCrumb;
        }
        else
        {
            crumbType = PlantCrumb;
        }
    }

    if (crumbType != VoidCrumb)
    {
        Vector2 mousePosition = GetMousePosition();

        // mousePosition = screen_to_snap(mousePosition);

        // int hitChunk = chunk_at(mousePosition);

        for (int i = 0; i < rows->count; i++)
        {
            handle_chunk_click(rows->world, rows->entities[i], &chunks[i], screen_to_world(mousePosition));
        }

        // if (hitChunk >= 0)
        // {
        //     // Instead of deleting and making another crumb we just alter the one we hit
        //     // hitCrumb->flavor = crumbType;
        // }
        // else
        // {
        //     spawn_crumb(rows->world, 0, mousePosition, crumbType);
        // }
    }
}

void ChunkManager(ecs_rows_t *rows)
{
    // XXX need playable column here
    Chunk *chunks = ecs_column(rows, Chunk, 1);

    // for every chunk.
    for (int i = 0; i < rows->count; i++)
    {
    }
}

void DebugHud(ecs_rows_t *rows)
{
    // Crumb *crumbs = ecs_column(rows, Crumb, 1);

    static bool show = true;

    if (IsKeyPressed(KEY_Q))
    {
        show = !show;
    }

    if (show)
    {
        char *message;

        asprintf(&message, "Crumb count: %d", rows->count);
        DrawTextEx(FontAlagard, message, (Vector2){.x = 10, .y = 5}, 20, 2, BRIGHT_WHITES);
        free(message);

        Vector2 mousePosition = GetMousePosition();

        // mousePosition = screen_to_snap(mousePosition);

        asprintf(&message, "Mouse position: %.2f, %.2f\n", mousePosition.x, mousePosition.y);
        DrawTextEx(FontAlagard, message, (Vector2){.x = 10, .y = 25}, 20, 2, BRIGHT_WHITES);
        free(message);

        Vector2 worldPosition = screen_to_world(mousePosition);

        asprintf(&message, "World position: %.2f, %.2f\n", worldPosition.x, worldPosition.y);
        DrawTextEx(FontAlagard, message, (Vector2){.x = 10, .y = 45}, 20, 2, BRIGHT_WHITES);
        free(message);

        Vector2 snapPostion = world_to_snap(worldPosition);
        Vector2 crumbPosition = snap_to_crumb(snapPostion);

        asprintf(&message, "Crumb position: %.2f, %.2f\n", crumbPosition.x, crumbPosition.y);
        DrawTextEx(FontAlagard, message, (Vector2){.x = 10, .y = 65}, 20, 2, BRIGHT_WHITES);
        free(message);

        Vector2 chunkPosition = world_to_chunk(worldPosition);

        asprintf(&message, "Chunk position: %.2f, %.2f\n", chunkPosition.x, chunkPosition.y);
        DrawTextEx(FontAlagard, message, (Vector2){.x = 10, .y = 85}, 20, 2, BRIGHT_WHITES);
        free(message);

        BeginMode2D(camera);
        DrawLine(camera.target.x, camera.target.y - 11, camera.target.x, camera.target.y + 10, FLAMINGO);
        DrawLine(camera.target.x - 10, camera.target.y, camera.target.x + 10, camera.target.y, FLAMINGO);
        EndMode2D();
    }
}

void Mover(ecs_rows_t *rows)
{
    Position *positions = ecs_column(rows, Position, 1);
    Velocity *velocities = ecs_column(rows, Velocity, 2);

    // Chunks are empty to begin with
    // WipeChunks();

    for (int i = 0; i < rows->count; i++)
    {
        positions[i].x += velocities[i].x;
        positions[i].y += velocities[i].y;

        // Need to tell the universe where this crumb lands
        // SetCrumb();
    }
}

void CameraSnapper(ecs_rows_t *rows)
{
    Position *positions = ecs_column(rows, Position, 1);

    camera.offset.x = positions[0].x;
    camera.offset.y = positions[0].y;
    camera.target.x = WINDOW_WIDTH_PX / 2 - camera.offset.x;
    camera.target.y = WINDOW_HEIGHT_PX / 2 - camera.offset.y;
}

void CrummySystemsImport(ecs_world_t *world, int id)
{
    ECS_MODULE(world, CrummySystems);

    ECS_SYSTEM(world, CrumbRenderer, EcsOnUpdate, Position, Crumb);
    ECS_SYSTEM(world, CrumbSimulator, EcsOnUpdate, Position, Velocity, Crumb);
    ECS_SYSTEM(world, MouseCrumber, EcsOnUpdate, Chunk);
    ECS_SYSTEM(world, Mover, EcsOnUpdate, Position, Velocity, ?Playable);

    ECS_SYSTEM(world, Input, EcsOnUpdate, Velocity, Playable);
    ECS_SYSTEM(world, CameraSnapper, EcsOnUpdate, Position, Playable);

    ECS_SYSTEM(world, DebugHud, EcsOnUpdate);

    ECS_SET_ENTITY(CrumbRenderer);
    ECS_SET_ENTITY(MouseCrumber);
    ECS_SET_ENTITY(CrumbSimulator);
    ECS_SET_ENTITY(Mover);
}

void Input(ecs_rows_t *rows)
{
    Velocity *velocities = ecs_column(rows, Velocity, 1);

    bool u = IsKeyDown(KEY_UP);
    bool d = IsKeyDown(KEY_DOWN);
    bool l = IsKeyDown(KEY_LEFT);
    bool r = IsKeyDown(KEY_RIGHT);

    float baseSpeed = 1 / camera.zoom;

    if (IsKeyDown(KEY_Z))
    {
        if (IsKeyDown(KEY_SPACE))
        {
            camera.zoom = 1.0;
        }
        else
        {
            camera.zoom += 0.1 * (IsKeyDown(KEY_LEFT_SHIFT) ? -0.8 : 1);

            camera.zoom = MIN(MAX(MIN_ZOOM, camera.zoom), MAX_ZOOM);
        }
    }

    // printf("input: %d\n", rows->count);

    for (int i = 0; i < rows->count; i++)
    {
        Vector2 targetVelocity = {.x = 0, .y = 0};

        if (u && l)
        {
            targetVelocity.x = -ROOT2OVER2 * CRUMB_SIZE * baseSpeed;
            targetVelocity.y = -ROOT2OVER2 * CRUMB_SIZE * baseSpeed;
        }
        else if (u && r)
        {
            targetVelocity.x = ROOT2OVER2 * CRUMB_SIZE * baseSpeed;
            targetVelocity.y = -ROOT2OVER2 * CRUMB_SIZE * baseSpeed;
        }
        else if (u)
        {
            targetVelocity.y = -CRUMB_SIZE * baseSpeed;
        }
        else if (d && l)
        {
            targetVelocity.x = -ROOT2OVER2 * CRUMB_SIZE * baseSpeed;
            targetVelocity.y = ROOT2OVER2 * CRUMB_SIZE * baseSpeed;
        }
        else if (d && r)
        {
            targetVelocity.x = ROOT2OVER2 * CRUMB_SIZE * baseSpeed;
            targetVelocity.y = ROOT2OVER2 * CRUMB_SIZE * baseSpeed;
        }
        else if (d)
        {
            targetVelocity.y = CRUMB_SIZE * baseSpeed;
        }
        else if (l)
        {
            targetVelocity.x = -CRUMB_SIZE * baseSpeed;
        }
        else if (r)
        {
            targetVelocity.x = CRUMB_SIZE * baseSpeed;
        }
        else
        {
            targetVelocity.x = 0.0;
            targetVelocity.y = 0.0;
        }

        if (IsKeyDown(KEY_LEFT_SHIFT))
        {
            targetVelocity.x *= 2;
            targetVelocity.y *= 2;
        }

        targetVelocity = Vector2Lerp(velocities[i], targetVelocity, 0.5);

        velocities[i].x = targetVelocity.x;
        velocities[i].y = targetVelocity.y;
    }
}
