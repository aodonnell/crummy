#ifndef _SYSTEMS_H
#define _SYSTEMS_H

#include "flecs.h"

typedef struct _crummy_systems
{
    ECS_DECLARE_ENTITY(CrumbRenderer);
    ECS_DECLARE_ENTITY(CrumSimulator);
    ECS_DECLARE_ENTITY(DebugHud);
    ECS_DECLARE_ENTITY(Mover);
} CrummySystems;

#define CrummySystemsImportHandles(handles)     \
    ECS_IMPORT_ENTITY(handles, CrumbRenderer);  \
    ECS_IMPORT_ENTITY(handles, CrumSimulator);  \
    ECS_IMPORT_ENTITY(handles, DebugHud);       \
    ECS_IMPORT_ENTITY(handles, Mover);

void CrummySystemsImport(ecs_world_t *world, int flags);

// Public systems
void Input(ecs_rows_t *rows);

#endif