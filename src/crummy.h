#ifndef _CRUMMY_H
#define _CRUMMY_H

#include <raylib.h>
#include <unqlite.h>

#define WINDOW_HEIGHT_PX 720
#define WINDOW_WIDTH_PX 1080

#define CRUMB_SIZE 8 

#define CHUNK_SIZE 64

#define CHUNK_SIZE_PX CRUMB_SIZE*CHUNK_SIZE

#define DANK_FACTOR 0.24

#define MAX_ZOOM 5
#define MIN_ZOOM 0.5

Font FontAlagard;
Camera2D camera;

extern char * universe;

#endif