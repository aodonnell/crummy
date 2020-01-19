#ifndef _COMPONENTS_H
#define _COMPONENTS_H

#include "raylib.h"
#include "flecs.h"

#include "core.h"

typedef struct _crummy_components
{
    ECS_DECLARE_COMPONENT(Position);
    ECS_DECLARE_COMPONENT(Velocity);
    ECS_DECLARE_COMPONENT(Crumb);
    ECS_DECLARE_ENTITY(Playable);
} CrummyComponents;

void CrummyComponentsImport(ecs_world_t *world, int flags);

#define CrummyComponentsImportHandles(handles) \
    ECS_IMPORT_COMPONENT(handles, Position);   \
    ECS_IMPORT_COMPONENT(handles, Velocity);   \
    ECS_IMPORT_COMPONENT(handles, Crumb);      \
    ECS_IMPORT_ENTITY(handles, Playable);

#endif