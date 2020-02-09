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

    int asnapx = FloatToSnapX(crumba.x);
    int asnapy = FloatToSnapY(crumba.y);
    int bsnapx = FloatToSnapX(crumbb.x);
    int bsnapy = FloatToSnapY(crumbb.y);

    return (asnapx == bsnapx && asnapy == bsnapy);
}

int FloatToSnapX(float pos)
{
    float crumbSize = CRUMB_SIZE;
    
    return (int)(pos - (int)pos % (int)(crumbSize));
}

int FloatToSnapY(float pos)
{
    float crumbSize = CRUMB_SIZE;
    
    return (int)(pos - (int)pos % (int)(crumbSize));
}

Vector2 Vector2ToSnap(Vector2 pos)
{
    pos.x = FloatToSnapX(pos.x);
    pos.y = FloatToSnapY(pos.y);

    return pos;
}

float ScreenToWorldX(float screenX)
{
    return (screenX - camera.target.x - camera.offset.x)/camera.zoom + camera.target.x;
}

float ScreenToWorldY(float screenY)
{
    return (screenY - camera.target.y - camera.offset.y)/camera.zoom + camera.target.y;
}

Vector2 ScreenToWorldPosition(Vector2 screenPosition)
{
    screenPosition.x = ScreenToWorldX(screenPosition.x);
    screenPosition.y = ScreenToWorldY(screenPosition.y);

    return screenPosition;
}

int RandInRange(int low, int high)
{
    return (rand() % (high - low + 1)) + low;
}

double Rand01()
{
    return rand()/(double)RAND_MAX;
}

