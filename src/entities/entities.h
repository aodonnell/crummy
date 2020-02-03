#ifndef _ENTITIES_H
#define _ENTITIES_H

#include "raylib.h"
#include "flecs.h"

#include "core.h"

ecs_entity_t SpawnCrumb(ecs_world_t * world , Vector2 position, CrumbFlavor type);

ecs_entity_t SpawnCCamera(ecs_world_t * world, Vector2 position);

#endif