#include <stdio.h>
#include <stdlib.h>

#include "core.h"
#include "crummy.h"

bool CrumbsHitting(Position crumba, Position crumbb)
{

    //  A_______
    //  |       |
    //  |    B__|___
    //  |____|      |
    //       |______|

    int asnapx = FloatToSnap(crumba.x);
    int asnapy = FloatToSnap(crumba.y);
    int bsnapx = FloatToSnap(crumbb.x);
    int bsnapy = FloatToSnap(crumbb.y);

    return (asnapx == bsnapx && asnapy == bsnapy);
}

int FloatToSnap(float pos)
{
    return (int)(pos - (int)pos % CRUMB_SIZE);
}

Vector2 Vector2ToSnap(Vector2 pos)
{
    pos.x = FloatToSnap(pos.x);
    pos.y = FloatToSnap(pos.y);

    return pos;
}

int RandInRange(int low, int high)
{
    return (rand() % (high - low + 1)) + low;
}

Color CrumbColorLookup[] =
    {
        // Void
        DUSK,

        // Rock
        PRETTY_IN_PINK,

        // Sand
        CREME,

        // Water
        BRILLIANT_BLUE,
};

int Chunk[CHUNK_SIZE * CHUNK_SIZE];

// XXX temporary chunk methods
int CrumbAt(Vector2 position)
{
    position.x = FloatToSnap(position.x);
    position.y = FloatToSnap(position.y);

    Vector2 chunkPosition = PixelToChunkPosition(position);

    if (chunkPosition.x >= 0 && chunkPosition.y >= 0 && chunkPosition.x < CHUNK_SIZE && chunkPosition.y < CHUNK_SIZE)
    {
        return Chunk[ChunkIndexFromChunkPosition(chunkPosition)];
    }

    return -1;
}

bool SetCrumb(Position position, int crumb)
{
    position.x = FloatToSnap(position.x);
    position.y = FloatToSnap(position.y);

    Vector2 chunkPosition = PixelToChunkPosition(position);

    if (chunkPosition.x >= 0 && chunkPosition.y >= 0 && chunkPosition.x < CHUNK_SIZE && chunkPosition.y < CHUNK_SIZE)
    {
        Chunk[ChunkIndexFromChunkPosition(chunkPosition)] = crumb;
        return true;
    }

    return false;
}

Vector2 PixelToChunkPosition(Position position)
{

    Vector2 chunkPosition = (Vector2){.x = (int)(position.x * CHUNK_SIZE / WORLD_WIDTH), .y = (int)(position.y * CHUNK_SIZE / WORLD_HEIGHT)};

    return chunkPosition;
}

int ChunkIndexFromChunkPosition(Vector2 chunkPosition)
{
    return (int)chunkPosition.x * CHUNK_SIZE + (int)chunkPosition.y;
}

void WipeChunk()
{
    memset(Chunk, -1, CHUNK_SIZE * CHUNK_SIZE * sizeof(int));
}