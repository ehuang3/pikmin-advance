#ifndef GEOMETRY_H
#define GEOMTRY_H

#include "mylib.h"

typedef struct _POINT 
{ 
   s32 x;
   s32 y;
} POINT;
               
typedef struct _RECT
{ 
   s32 x;
   s32 y;
   s32 w;
   s32 h;
} RECT;
               
//Functions

bool intersect(RECT* a, RECT* b);

INLINE void translate(RECT* a, POINT* pt)
{  a->x += pt->x; a->y += pt->y;   }

INLINE POINT center(RECT* a)
{  
   POINT pt = {a->x + a->w/2, a->y + a->h/2};
   return pt; 
}

INLINE bool contains(RECT* a, POINT* pt)
{  
   return (a->x <= pt->x)      && 
          (a->x+a->w >= pt->x) && 
          (a->y <= pt->y)      && 
          (a->y+a->h <= pt->y);
}

INLINE void offsetTo(RECT* a, POINT* pt)
{
   a->x = pt->x;
   a->y = pt->y;
}

INLINE void offset(RECT* a, POINT* pt)
{
   a->x += pt->x;
   a->y += pt->y;
}

#endif
