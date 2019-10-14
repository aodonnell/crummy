#ifndef _SYSTEMS_H
#define _SYSTEMS_H

#include "flecs.h"

typedef struct _crummy_systems
{
    ECS_DECLARE_ENTITY(SpriteRenderer);
} CrummySystems;

#define CrummySystemsImportHandles(handles)\
    ECS_IMPORT_ENTITY(handles, SpriteRenderer);

void CrummySystemsImport(ecs_world_t * world, int flags);

#endif