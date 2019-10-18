#include "systems.h"

#include "raylib.h"

#include "components.h"

void SpriteRenderer(ecs_rows_t * rows)
{
    Position * positions = ecs_column(rows, Position, 1);
    Sprite * sprites = ecs_column(rows, Sprite, 2);

    BeginDrawing();
    ClearBackground(RAYWHITE);

    for(int i = 0; i < rows->count; i++)
    {
        /* 
        * TODO maybe add something in the sprite about if it is positioned 
        * from the center, 
        * the corner,
        * or a defined offset anchor
        */
        DrawTexture(sprites[i].texture, positions[i].x, positions[i].y, WHITE);
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

    for(int i = 0; i < rows->count; i++)
    {
        // If moving, then move
        if(IsKeyDown(KEY_UP))
        {
            velocities[i].y = -1.0;
        }
        else if(IsKeyDown(KEY_DOWN))
        {
            velocities[i].y = 1.0;
        }
        else if(IsKeyDown(KEY_LEFT))
        {
            velocities[i].x = -1.0;
        }
        else if(IsKeyDown(KEY_RIGHT))
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

    ECS_SYSTEM(world, SpriteRenderer, EcsOnUpdate, Position, Sprite);
    ECS_SYSTEM(world, Mover, EcsOnUpdate, Position, Velocity);
    ECS_SYSTEM(world, Input, EcsOnUpdate, Velocity, Playable);

    ECS_SET_ENTITY(SpriteRenderer);
    ECS_SET_ENTITY(Mover);
}