#include <stdio.h>

#include "raylib.h"

#include "colours.h"
#include "crummy.h"
#include "core.h"
#include "components.h"
#include "entities.h"
#include "systems.h"

void CrumbRenderer(ecs_rows_t * rows)
{
    Position * positions = ecs_column(rows, Position, 1);
    Crumb * crumbs = ecs_column(rows, Crumb, 2);

    for(int i = 0; i < rows->count; i++)
    {
        int snapx = (int)(positions[i].x - (int)positions[i].x % CRUMB_SIZE);
        int snapy = (int)(positions[i].y - (int)positions[i].y % CRUMB_SIZE);

        DrawRectangle(snapx, snapy, CRUMB_SIZE, CRUMB_SIZE, crumbs[i].color);
    }    
}

void MouseCrumber(ecs_rows_t * rows)
{

    bool rightClicked = IsMouseButtonPressed(MOUSE_RIGHT_BUTTON);
    bool leftClicked = IsMouseButtonPressed(MOUSE_LEFT_BUTTON);

    Vector2 mousePosition = GetMousePosition();

    // printf("Mouse at x: %.2f, y: %.2f\n", mousePosition.x, mousePosition.y);

    if(leftClicked)
    {
        SpawnCrumb(rows->world, mousePosition);
        printf("Spawned crumb at x: %.2f, y: %.2f", mousePosition.x, mousePosition.y);
    }
}

void Mover(ecs_rows_t * rows)
{
    Position * positions = ecs_column(rows, Position, 1);
    Velocity * velocities = ecs_column(rows, Velocity, 2);

    for (int i = 0; i < rows->count; i++)
    {
       positions[i].x += velocities[i].x;
       positions[i].y += velocities[i].y;
    }
}

void Input(ecs_rows_t * rows)
{
    // XXX this is only going to be for debugging but the movement should be based more on changing the direction in terms of where the movement vector should point in the same direction of the face of the playable entitiy 
    Velocity * velocities = ecs_column(rows, Velocity, 1);

    bool u = IsKeyDown(KEY_UP);
    bool d = IsKeyDown(KEY_DOWN);
    bool l = IsKeyDown(KEY_LEFT);
    bool r = IsKeyDown(KEY_RIGHT);    

    for(int i = 0; i < rows->count; i++)
    {
        // If moving, then move
        if(u)
        {
            velocities[i].y = -CRUMB_SIZE;
        }
        else if(d)
        {
            velocities[i].y = CRUMB_SIZE;
        }
        else if(l)
        {
            velocities[i].x = -CRUMB_SIZE;
        }
        else if(r)
        {
            velocities[i].x = CRUMB_SIZE;
        }
        else
        {
            velocities[i].x = 0.0;
            velocities[i].y = 0.0;
        }
    }
}

void CrummySystemsImport(ecs_world_t * world, int id)
{
    ECS_MODULE(world, CrummySystems);

    ECS_SYSTEM(world, CrumbRenderer, EcsOnUpdate, Position, Crumb);
    ECS_SYSTEM(world, Mover, EcsOnUpdate, Position, Velocity);
    ECS_SYSTEM(world, Input, EcsOnUpdate, Velocity, Playable);
    ECS_SYSTEM(world, MouseCrumber, EcsOnUpdate, 0);

    ECS_SET_ENTITY(CrumbRenderer);
    ECS_SET_ENTITY(Mover);
}