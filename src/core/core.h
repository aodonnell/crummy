#ifndef _CORE_H
#define _CORE_H

#include "handling.h"
#include "components.h"

#include <stdint.h>

#define ROOT2OVER2 0.7071

bool CrumbsHitting(Position crumba, Position crumbb);

int FloatToSnap(float pos);

int RandInRange(int low, int high);

#endif