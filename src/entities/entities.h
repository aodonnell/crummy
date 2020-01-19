#ifndef _ENTITIES_H
#define _ENTITIES_H

#include "raylib.h"
#include "flecs.h"

ecs_entity_t SpawnCrumb(ecs_world_t *world, Vector2 position);

ecs_entity_t SpawnPlayableCrumb(ecs_world_t *world, Vector2 position);

#endif