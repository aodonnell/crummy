#include "raylib.h"

#include "colours.h"
#include "core.h"
#include "components.h"
#include "systems.h"

void CrumbRenderer(ecs_rows_t * rows)
{
    Position * positions = ecs_column(rows, Position, 1);

    BeginDrawing();
    ClearBackground(DUSK);

    for(int i = 0; i < rows->count; i++)
    {
        DrawRectangle(positions[i].x, positions[i].y, 4, 4, CREME);
    }
    
    EndDrawing();
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
            velocities[i].y = -1.0;
        }
        else if(d)
        {
            velocities[i].y = 1.0;
        }
        else if(l)
        {
            velocities[i].x = -1.0;
        }
        else if(r)
        {
            velocities[i].x = 1.0;
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

    ECS_SET_ENTITY(CrumbRenderer);
    ECS_SET_ENTITY(Mover);
}