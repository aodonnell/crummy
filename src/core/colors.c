#include "colors.h"
#include "crumbmath.h"

Color rand_color()
{
    return (Color){rand_in_range(0, 0xff), rand_in_range(0, 0xff), rand_in_range(0, 0xff), 0xff};
}

Color rand_tint()
{
    Color color = rand_color();

    color.a = 0x44;

    return color;
}