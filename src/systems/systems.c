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
        DrawTexture(sprites[i].texture, positions[i].x, positions[i].y, WHITE);
    }
    
    EndDrawing();
}

void ControllerMover(ecs_rows_t * rows)
{

}

void CrummySystemsImport(ecs_world_t * world, int id)
{
    ECS_MODULE(world, CrummySystems);

    ECS_SYSTEM(world, SpriteRenderer, EcsOnUpdate, Position, Sprite);

    ECS_SET_ENTITY(SpriteRenderer);
}