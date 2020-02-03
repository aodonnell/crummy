#include <stdio.h>
#include <stdlib.h>

#include "core.h"
#include "crummy.h"

Color CrumbColorLookup[] =
    {
        // Void
        DUSK,

        // Rock
        ROCKS_USED_TO_BE_PINK_Y_KNOW,

        // Sand
        CREME,

        // Water
        BRILLIANT_BLUE,

        // Plant
        SOMETHING_GREEN,
};

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

double Rand01()
{
    return rand()/(double)RAND_MAX;
}

