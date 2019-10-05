#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "raylib.h"

typedef struct _physicalComponent 
{
    Vector2 position;
} PhysicalC;

typedef struct _sprite
{
    Texture2D texture;    
} SpriteC;

#endif