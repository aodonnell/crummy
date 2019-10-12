#ifndef COMPONENTS_H
#define COMPONENTS_H

#include "raylib.h"

typedef struct _positional_omponent 
{
    Vector2 position;
} Position;

typedef struct _sprite_component
{
    Texture2D texture;    
} Sprite;

#endif