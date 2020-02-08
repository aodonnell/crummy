#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "raylib.h"

#include "colors.h"
#include "crummy.h"

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
    Camera2D *cameras = ecs_column(rows, Camera2D, 3);

    printf("In renderer. Rows: %d\n", rows->count);
    printf("target: %.2f, %.2f\n", camera.target.x, camera.target.y);

    DrawRectangle(camera.target.x+camera.offset.x, camera.target.y+camera.offset.y, CRUMB_SIZE, CRUMB_SIZE, FLAMINGO);

    for (int i = 0; i < rows->count; i++)
    {
        int snapx = FloatToSnap(positions[i].x);
        int snapy = FloatToSnap(positions[i].y);

        DrawRectangle(snapx, snapy, CRUMB_SIZE, CRUMB_SIZE, CrumbColorLookup[crumbs[i].flavor]);
    }
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
                //     else if((sewater && swwater && Rand01() < 0.5) || (sewater && !swwater))
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
                else if ((sw && se && Rand01() > 0.5) || (sw && !se))
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

                if((se >= 0 && crumbs[se].flavor == PlantCrumb)        \
                    || (sw >= 0 && crumbs[sw].flavor == PlantCrumb)    \
                    || (s >= 0 && crumbs[s].flavor == PlantCrumb))     \
                {
                    if(Rand01() < DANK_FACTOR)
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
                else if ((sw && se && Rand01() > 0.5) || (sw && !se))
                {
                    targetV.x = -ROOT2OVER2 * baseSpeed;
                    targetV.y = ROOT2OVER2 * baseSpeed;
                }
                else if (se)
                {
                    targetV.x = ROOT2OVER2 * baseSpeed;
                    targetV.y = ROOT2OVER2 * baseSpeed;
                }
                else if((e && w && Rand01() > 0.5) || (e && !w))
                {
                    targetV.x = baseSpeed;
                    targetV.y = 0;
                }
                else if(w)
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
    Position *positions = ecs_column(rows, Position, 1);
    Crumb *crumbs = ecs_column(rows, Crumb, 2);

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
            crumbType = PlantCrumb;
        }
        else
        {
            crumbType = RockCrumb;
        }
    }

    if (crumbType != VoidCrumb)
    {
        Vector2 mousePosition = Vector2ToSnap(GetMousePosition());

        Crumb *hitCrumb = NULL;

        // int crumb = CrumbAt(mousePosition);

        // if (crumb > 0)
        // {
        //     hitCrumb = &crumbs[crumb];
        // }

        if (hitCrumb)
        {
            // Instead of deleting and making another crumb we just alter the one we hit
            hitCrumb->flavor = crumbType;
        }
        else
        {
            SpawnCrumb(rows->world, mousePosition, crumbType);
        }
    }
}

void ChunkManager(ecs_rows_t *rows)
{
    // XXX need playable column here
    Chunk * chunks = ecs_column(rows, Chunk, 1);

    // for every chunk.
    for(int i = 0; i < rows->count; i++)
    {

    }
}

void DebugHud(ecs_rows_t *rows)
{
    Position *positions = ecs_column(rows, Position, 1);
    Crumb *crumbs = ecs_column(rows, Crumb, 2);

    char *message;

    asprintf(&message, "Crumb count: %d", rows->count);

    DrawTextEx(FontAlagard, message, (Vector2){.x = 10, .y = 5}, 20, 2, BRIGHT_WHITES);

    free(message);
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
    Camera2D *cameras = ecs_column(rows, Camera2D, 2);


    for(int i = 0; i < rows->count; i++)
    {
        printf("boom: %.2f, %.2f\n", positions[i].x, positions[i].y);
        camera.target = positions[i];
    }
}

void CrummySystemsImport(ecs_world_t *world, int id)
{
    ECS_MODULE(world, CrummySystems);

    ECS_SYSTEM(world, CrumbRenderer, EcsOnUpdate, Position, Crumb, SYSTEM.Camera2D);
    ECS_SYSTEM(world, CrumbSimulator, EcsOnUpdate, Position, Velocity, Crumb);
    ECS_SYSTEM(world, MouseCrumber, EcsOnUpdate, ?Position, ?Crumb);
    ECS_SYSTEM(world, Mover, EcsOnUpdate, Position, Velocity);
    ECS_SYSTEM(world, CameraSnapper, EcsOnUpdate, Position, Camera2D);

    ECS_SYSTEM(world, Input, EcsOnUpdate, Velocity, Playable);

    ECS_SYSTEM(world, DebugHud, EcsOnUpdate, Position, Crumb);

    ECS_SET_ENTITY(CrumbRenderer);
    ECS_SET_ENTITY(MouseCrumber);
    ECS_SET_ENTITY(CrumbSimulator);
    ECS_SET_ENTITY(CameraSnapper);
    ECS_SET_ENTITY(Mover);
}

void Input(ecs_rows_t *rows)
{
    // XXX this is only going to be for debugging but the movement should be based more on changing the direction in terms of where the movement vector should point in the same direction of the face of the playable entitiy
    Velocity *velocities = ecs_column(rows, Velocity, 1);

    bool u = IsKeyDown(KEY_UP);
    bool d = IsKeyDown(KEY_DOWN);
    bool l = IsKeyDown(KEY_LEFT);
    bool r = IsKeyDown(KEY_RIGHT);

    for (int i = 0; i < rows->count; i++)
    {
        Vector2 targetVelocity = {.x = 0, .y = 0};

        if (u && l)
        {
            targetVelocity.x = -ROOT2OVER2 * CRUMB_SIZE;
            targetVelocity.y = -ROOT2OVER2 * CRUMB_SIZE;
        }
        else if (u && r)
        {
            targetVelocity.x = ROOT2OVER2 * CRUMB_SIZE;
            targetVelocity.y = -ROOT2OVER2 * CRUMB_SIZE;
        }
        else if (u)
        {
            targetVelocity.y = -CRUMB_SIZE;
        }
        else if (d && l)
        {
            targetVelocity.x = -ROOT2OVER2 * CRUMB_SIZE;
            targetVelocity.y = ROOT2OVER2 * CRUMB_SIZE;
        }
        else if (d && r)
        {
            targetVelocity.x = ROOT2OVER2 * CRUMB_SIZE;
            targetVelocity.y = ROOT2OVER2 * CRUMB_SIZE;
        }
        else if (d)
        {
            targetVelocity.y = CRUMB_SIZE;
        }
        else if (l)
        {
            targetVelocity.x = -CRUMB_SIZE;
        }
        else if (r)
        {
            targetVelocity.x = CRUMB_SIZE;
        }
        else
        {
            targetVelocity.x = 0.0;
            targetVelocity.y = 0.0;
        }

        // targetVelocity = Vector2Lerp(velocities[i], targetVelocity, 0.5);

        velocities[i].x = targetVelocity.x;
        velocities[i].y = targetVelocity.y;
    }
}
