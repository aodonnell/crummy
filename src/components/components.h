#ifndef _COMPONENTS_H
#define _COMPONENTS_H

#include "raylib.h"
#include "flecs.h"

typedef struct Vector2 Position;

typedef struct Vector2 Velocity;

typedef struct _sprite_component
{
    Texture2D texture;
} Sprite;

typedef struct _crumb 
{
    Color color;
} Crumb;

typedef struct _crummy_components
{
    ECS_DECLARE_COMPONENT(Position);
    ECS_DECLARE_COMPONENT(Velocity);
    ECS_DECLARE_COMPONENT(Sprite);
    ECS_DECLARE_COMPONENT(Crumb);
    ECS_DECLARE_ENTITY(Playable);
} CrummyComponents;

void CrummyComponentsImport(ecs_world_t *world, int flags);

#define CrummyComponentsImportHandles(handles) \
    ECS_IMPORT_COMPONENT(handles, Position);   \
    ECS_IMPORT_COMPONENT(handles, Velocity);   \
    ECS_IMPORT_COMPONENT(handles, Sprite);     \
    ECS_IMPORT_COMPONENT(handles, Crumb);      \
    ECS_IMPORT_ENTITY(handles, Playable);

#endif