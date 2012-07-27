#include "geometry.h"

bool intersect(RECT* a, RECT* b)
{
   return ~((a->pt.x + a->w < b->pt.x) ||
            (a->pt.x > b->pt.x + b->w) ||
            (a->pt.y - a->h > b->pt.y) ||
            (a->pt.y < b->pt.y - b->h));
}
