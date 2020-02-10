#ifndef _ENTITIES_H
#define _ENTITIES_H

#include "raylib.h"
#include "flecs.h"

#include "core.h"

ecs_entity_t spawn_crumb(ecs_world_t *world, ecs_entity_t parentChunk, Vector2 position, CrumbFlavor flavor);

ecs_entity_t spawn_camera_2d(ecs_world_t *world, Vector2 position, Camera2D *camera);

ecs_entity_t spawn_chunk(ecs_world_t *world, Vector2 corner, Crumb *crumbData);

#endif