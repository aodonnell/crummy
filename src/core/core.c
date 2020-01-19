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

int RandInRange(int low, int high)
{
    return (rand() % (high - low + 1)) + low; 
}