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

    BeginMode2D(camera);

    for (int i = 0; i < rows->count; i++)
    {
        DrawRectangle(positions[i].x, positions[i].y, CRUMB_SIZE, CRUMB_SIZE, CrumbColorLookup[crumbs[i].flavor]);
    }

    EndMode2D();
}

void ChunkRenderer(ecs_rows_t *rows)
{
    Chunk *chunks = ecs_column(rows, Chunk, 1);

    BeginMode2D(camera);

    int l = CHUNK_SIZE * CRUMB_SIZE;

    for (int i = 0; i < rows->count; i++)
    {
        Vector2 worldPosition = chunk_to_world(chunks[i].corner);
        DrawRectangle(worldPosition.x, worldPosition.y, l, l, chunks[i].color);
    }

    EndMode2D();
}

void CrumbSimulator(ecs_rows_t *rows)
{
    Chunk *chunk = ecs_column(rows, Chunk, 1);
    Position *positions = ecs_column(rows, Position, 2);
    Velocity *velocities = ecs_column(rows, Velocity, 3);
    Crumb *crumbs = ecs_column(rows, Crumb, 4);

    CrumbNeighborSet set;

    int sewater = 0;
    int swwater = 0;
    int swater = 0;

    float baseSpeed = CRUMB_SIZE;

    Vector2 targetV;

    printf("crumbs: %d\n", rows->count);

    for (int i = 0; i < rows->count; i++)
    {
        Vector4 chunkPosition = world_to_chunk_and_crumb(positions[i]);

        set = get_crumb_neighbor_set(chunk, (Vector2){.x = chunkPosition.z, .y = chunkPosition.w});
        // printf("set: %d, %d, %d, %d, %d, %d, %d, %d\n", set.n, set.ne, set.e, set.se, set.s, set.sw, set.w, set.nw);

        switch (crumbs[i].flavor)
        {
        case VoidCrumb:
            // XXX delete the crumb if it was set to void?
            break;
        case SandCrumb:

            set.e = set.e < 0;
            set.w = set.w < 0;
            set.s = set.s < 0;

            set.se = set.se < 0 && set.e;
            set.sw = set.sw < 0 && set.w;

            if (set.s)
            {
                targetV.x = 0;
                targetV.y = baseSpeed;
            }
            else if ((set.sw && set.se && rand01() > 0.5) || (set.sw && !set.se))
            {
                targetV.x = -ROOT2OVER2 * baseSpeed;
                targetV.y = ROOT2OVER2 * baseSpeed;
            }
            else if (set.se)
            {
                targetV.x = ROOT2OVER2 * baseSpeed;
                targetV.y = ROOT2OVER2 * baseSpeed;
            }
            else
            {
                targetV.x = 0;
                targetV.y = 0;
            }

            velocities[i] = targetV;
            // velocities[i] = Vector2Lerp(velocities[i], targetV, 0.5);
            break;

        case WaterCrumb:

            if ((set.se >= 0 && crumbs[set.se].flavor == PlantCrumb) || (set.sw >= 0 && crumbs[set.sw].flavor == PlantCrumb) || (set.s >= 0 && crumbs[set.s].flavor == PlantCrumb))
            {
                if (rand01() < DANK_FACTOR)
                {
                    crumbs[i].flavor = PlantCrumb;
                    velocities[i].x = 0;
                    velocities[i].y = 0;
                }
                break;
            }

            set.e = set.e < 0;
            set.w = set.w < 0;
            set.s = set.s < 0;

            set.se = set.se < 0 && set.e;
            set.sw = set.sw < 0 && set.w;

            if (set.s)
            {
                targetV.x = 0;
                targetV.y = baseSpeed;
            }
            else if ((set.sw && set.se && rand01() > 0.5) || (set.sw && !set.se))
            {
                targetV.x = -ROOT2OVER2 * baseSpeed;
                targetV.y = ROOT2OVER2 * baseSpeed;
            }
            else if (set.se)
            {
                targetV.x = ROOT2OVER2 * baseSpeed;
                targetV.y = ROOT2OVER2 * baseSpeed;
            }
            else if ((set.e && set.w && rand01() > 0.5) || (set.e && !set.w))
            {
                targetV.x = baseSpeed;
                targetV.y = 0;
            }
            else if (set.w)
            {
                targetV.x = -baseSpeed;
                targetV.y = 0;
            }
            else
            {
                targetV.x = 0;
                targetV.y = 0;

                velocities[i] = targetV;
            }

            velocities[i] = Vector2Lerp(velocities[i], targetV, 0.5);

            velocities[i] = targetV;

            break;

        default:
            break;
        }
    }
}

void MouseCrumber(ecs_rows_t *rows)
{
    // Position *positions = ecs_column(rows, Position, 1);

    Chunk *chunk = ecs_column(rows, Chunk, 1);
    Crumb *crumbs = ecs_column(rows, Crumb, 2);

    bool rightDown = IsMouseButtonDown(MOUSE_RIGHT_BUTTON);
    bool leftDown = IsMouseButtonDown(MOUSE_LEFT_BUTTON);

    Vector2 mousePosition = GetMousePosition();

    Vector2 worldPosition = screen_to_world(mousePosition);

    Vector4 chunkAndCrumb = world_to_chunk_and_crumb(worldPosition);

    if (chunkAndCrumb.x != chunk->corner.x || chunkAndCrumb.y != chunk->corner.y)
    {
        return;
    }

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
        int crumbHere = get_crumb_on_chunk(chunk, (Vector2){.x = chunkAndCrumb.z, .y = chunkAndCrumb.w});

        if (crumbHere < 0)
        {
            spawn_crumb(rows->world, chunk->id, world_to_snap(worldPosition), crumbType);
        }
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

        Vector4 dad = world_to_chunk_and_crumb(worldPosition);

        asprintf(&message, "Chunk and crumb position: %.2f, %.2f, %.2f, %.2f\n", dad.x, dad.y, dad.z, dad.w);
        DrawTextEx(FontAlagard, message, (Vector2){.x = 10, .y = 105}, 20, 2, BRIGHT_WHITES);
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

void CrumbMover(ecs_rows_t *rows)
{
    Chunk *chunk = ecs_column(rows, Chunk, 1);
    Crumb *crumbs = ecs_column(rows, Crumb, 2);
    Position *positions = ecs_column(rows, Position, 3);
    Velocity *velocities = ecs_column(rows, Velocity, 4);

    // should chunk mechanics just go here?
    Vector4 chunkPosition;

    Vector2 targetPosition;

    // Chunks are empty to begin with
    wipe_chunk(chunk);

    for (int i = 0; i < rows->count; i++)
    {
        targetPosition.x = positions[i].x + velocities[i].x;
        targetPosition.y = positions[i].y + velocities[i].y;

        chunkPosition = world_to_chunk_and_crumb(targetPosition);
        bool sameChunk = chunkPosition.x == chunk->corner.x &&
                         chunkPosition.y == chunk->corner.y;

        if (sameChunk)
        {
            positions[i] = targetPosition;

            positions[i] = world_to_snap(positions[i]);
        }

        chunkPosition = world_to_chunk_and_crumb(positions[i]);

        // Need to tell the universe where this crumb lands
        set_crumb_on_chunk(chunk, (Vector2){.x = chunkPosition.z, .y = chunkPosition.w}, rows->entities[i]);
    }
    // chunk_monitor(chunk);
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

    ECS_SYSTEM(world, ChunkRenderer, EcsOnUpdate, Chunk);
    ECS_SYSTEM(world, CrumbRenderer, EcsOnUpdate, Position, Crumb);
    ECS_SYSTEM(world, CrumbMover, EcsOnUpdate, CONTAINER.Chunk, Crumb, Position, Velocity);
    ECS_SYSTEM(world, CrumbSimulator, EcsOnUpdate, CONTAINER.Chunk, Position, Velocity, Crumb);
    ECS_SYSTEM(world, Mover, EcsOnUpdate, Position, Velocity, Playable, !Crumb);
    ECS_SYSTEM(world, MouseCrumber, EcsOnUpdate, CONTAINER.Chunk, Crumb, Position, Velocity);

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
