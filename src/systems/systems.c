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

// xxx no type safety
#define MIN(a, b) (((a) < (b)) ? (a) : (b))
#define MAX(a, b) (((a) > (b)) ? (a) : (b))

void CrumbRenderer(ecs_rows_t *rows)
{
    Position *positions = ecs_column(rows, Position, 1);
    Crumb *crumbs = ecs_column(rows, Crumb, 2);

    for (int i = 0; i < rows->count; i++)
    {
        int snapx = FloatToSnap(positions[i].x);
        int snapy = FloatToSnap(positions[i].y);

        DrawRectangle(snapx, snapy, CRUMB_SIZE, CRUMB_SIZE, CrumbColorLookup[crumbs[i].type]);
    }
}

void CrumbSimulator(ecs_rows_t *rows)
{
    Position *positions = ecs_column(rows, Position, 1);
    Velocity *velocities = ecs_column(rows, Velocity, 2);
    Crumb *crumbs = ecs_column(rows, Crumb, 3);

    bool n, ne, e, se, s, sw, w, nw;

    float baseSpeed = CRUMB_SIZE / 2;

    for (int i = 0; i < rows->count; i++)
    {
        switch (crumbs[i].type)
        {
        case VoidCrumb:
            // XXX delete the crumb if it was set to void?
            break;
        case SandCrumb:

            s = CrumbAt((Position){.x = positions[i].x, .y = positions[i].y + CRUMB_SIZE}) < 0;
            sw = CrumbAt((Position){.x = positions[i].x - CRUMB_SIZE, .y = positions[i].y + CRUMB_SIZE}) < 0;
            sw &= CrumbAt((Position){.x = positions[i].x - CRUMB_SIZE, .y = positions[i].y}) < 0;
            se = CrumbAt((Position){.x = positions[i].x + CRUMB_SIZE, .y = positions[i].y + CRUMB_SIZE}) < 0;
            se &= CrumbAt((Position){.x = positions[i].x + CRUMB_SIZE, .y = positions[i].y}) < 0;

            if (s)
            {
                velocities[i].x = 0;
                velocities[i].y = baseSpeed;
            }
            else if (sw && se && rand() > 0.5)
            {
                velocities[i].x = -ROOT2OVER2 * baseSpeed;
                velocities[i].y = ROOT2OVER2 * baseSpeed;
            }
            else if (se)
            {
                velocities[i].x = ROOT2OVER2 * baseSpeed;
                velocities[i].y = ROOT2OVER2 * baseSpeed;
            }
            else if (sw)
            {
                velocities[i].x = -ROOT2OVER2 * baseSpeed;
                velocities[i].y = ROOT2OVER2 * baseSpeed;
            }
            else
            {
                velocities[i].x = 0;
                velocities[i].y = 0;
            }

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

    CrumbType crumbType = VoidCrumb;

    if (rightDown && !leftDown)
    {
        crumbType = SandCrumb;
    }
    else if (!rightDown && leftDown)
    {
        crumbType = RockCrumb;
    }

    if (crumbType != VoidCrumb)
    {
        Vector2 mousePosition = Vector2ToSnap(GetMousePosition());

        Crumb *hitCrumb = NULL;

        int crumb = CrumbAt(mousePosition);

        if (crumb > 0)
        {
            hitCrumb = &crumbs[crumb];
        }

        if (hitCrumb)
        {
            // TODO If we hit a crumb, we need to simulate the effects of them colliding

            // Instead of deleting and making another crumb we just alter the one we hit
            Color rand = {RandInRange(0, 0xff), RandInRange(0, 0xff), RandInRange(0, 0xff), 0xff};
            hitCrumb->type = crumbType;
        }
        else
        {
            SpawnCrumb(rows->world, mousePosition, crumbType);
        }
    }
}

void DebugHud(ecs_rows_t *rows)
{
    Position *positions = ecs_column(rows, Position, 1);
    Crumb *crumbs = ecs_column(rows, Crumb, 2);

    char *message;

    asprintf(&message, "Crumb count: %d", rows->count);

    DrawTextEx(FontAlagard, message, (Vector2){.x = 10, .y = 5}, 20, 2, CREME);

    free(message);
}

void Mover(ecs_rows_t *rows)
{
    Position *positions = ecs_column(rows, Position, 1);
    Velocity *velocities = ecs_column(rows, Velocity, 2);

    WipeChunk();

    for (int i = 0; i < rows->count; i++)
    {
        positions[i].x += velocities[i].x;
        positions[i].y += velocities[i].y;

        positions[i].x = MIN(MAX(positions[i].x, 0), WORLD_WIDTH - CRUMB_SIZE);
        positions[i].y = MIN(MAX(positions[i].y, 0), WORLD_HEIGHT - CRUMB_SIZE);

        SetCrumb(positions[i], i);
    }
}

void CrummySystemsImport(ecs_world_t *world, int id)
{
    ECS_MODULE(world, CrummySystems);

    ECS_SYSTEM(world, CrumbRenderer, EcsOnUpdate, Position, Crumb);
    ECS_SYSTEM(world, CrumbSimulator, EcsOnUpdate, Position, Velocity, Crumb);
    ECS_SYSTEM(world, MouseCrumber, EcsOnUpdate, Position, Crumb);
    ECS_SYSTEM(world, Mover, EcsOnUpdate, Position, Velocity);
    ECS_SYSTEM(world, Input, EcsOnUpdate, Velocity, Playable);

    ECS_SYSTEM(world, DebugHud, EcsOnUpdate, Position, Crumb);

    ECS_SET_ENTITY(CrumbRenderer);
    ECS_SET_ENTITY(MouseCrumber);
    ECS_SET_ENTITY(CrumbSimulator);
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

        targetVelocity = Vector2Lerp(velocities[i], targetVelocity, 0.5);

        velocities[i].x = targetVelocity.x;
        velocities[i].y = targetVelocity.y;
    }
}
