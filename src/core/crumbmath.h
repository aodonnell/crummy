#ifndef _CRUMBMATH_H
#define _CRUMBMATH_H

#include <raylib.h>

Vector2 Vector2Lerp(Vector2 current, Vector2 target, float by);

int snap_to_crumb_x(float snapX);

int snap_to_crumb_y(float snapY);

Vector2 snap_to_crumb(Vector2 snap);

int world_to_crumb_x(float worldX);

int world_to_crumb_y(float worldY);

Vector2 world_to_crumb(Vector2 world);

int world_to_snap_x(float worldX);

int world_to_snap_y(float worldY);

Vector2 world_to_snap(Vector2 world);

float screen_to_world_x(float screenX);

float screen_to_world_y(float screenY);

Vector2 screen_to_world(Vector2 screen);

float world_to_screen_x(float worldX);

float world_to_screen_y(float worldY);

Vector2 world_to_screen(Vector2 world);

float world_to_chunk_x(float worldX);

float world_to_chunk_y(float worldY);

Vector2 world_to_chunk(Vector2 world);

float chunk_to_world_x(float worldX);

float chunk_to_world_y(float worldY);

Vector2 chunk_to_world(Vector2 world);

Vector4 world_to_chunk_and_crumb(Vector2 world);

float screen_to_snap_x(float screenX);

float screen_to_snap_y(float screenY);

Vector2 screen_to_snap(Vector2 screen);

int crumb_index_from_position(Vector2 position);

int rand_in_range(int low, int high);

double rand01();
#endif