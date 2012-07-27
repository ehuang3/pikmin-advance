#ifndef SHAPE_H
#define SHAPE_H

#include "mylib.h"

/* Typedefs of shapes */

/* Defines for shape-type checking */
#define POINT_SHAPE  1
#define LINE_SHAPE   2
#define RECT_SHAPE   4
#define CIRC_SHAPE   8
#define POLY_SHAPE   16
#define BMAP_SHAPE   32

typedef struct POINT
{
   s32 x;
   s32 y;
} ALIGN4 POINT;

typedef struct LINE
{
   POINT pt[2];
} ALIGN4 LINE;

typedef struct SEG
{
   POINT pt[2];
} ALIGN4 SEG;

typedef struct RECT
{
   POINT pt[2];
} ALIGN4 RECT;

typedef struct CIRC
{
   POINT orig;
   u32 radius;
} ALIGN4 CIRC;

/* A Poly shape contains an vertex array. The end of the array is marked by the 
NULL (0) pointer. */
typedef struct POLY
{
   POINT* verts;
} ALIGN4 POLY;

/* A bitmap shape is an array of pointers to tile addresses ordered in 1D array
form. The end of the array is delimited by a NULL (0) pointer. */
typedef struct BMAP
{
   POINT* orig;
   u32 w;
   u32 h;
   TILE** tiles;
} ALIGN4 BMAP;


/* Function prototypes */
INLINE POINT point(s32 x, s32 y);
INLINE POINT add(POINT* src, POINT* op);
INLINE POINT sub(POINT* src, POINT* op);
INLINE POINT neg(POINT* pt);
INLINE int dot(POINT* op1, POINT* op2);
INLINE POINT mult(POINT* src, s32 op);
INLINE POINT delta(POINT* start, POINT* end);
INLINE u32 magsq(POINT* pt);

INLINE LINE line(s32 x1, s32 y1, s32 x2, s32 y2);
INLINE LINE line(POINT* pt1, POINT* pt2);
INLINE POINT delta(LINE* l);

INLINE RECT rect(s32 x1, s32 y1, s32 x2, s32 y2);
INLINE RECT rect(POINT* pt1, POINT* pt2);
void offset(RECT* dst, RECT* op1, POINT* op2);
void offsetTo(RECT* dst, RECT* op1, POINT* op2);
INLINE u32 width(RECT* r);
INLINE u32 height(RECT* r);
INLINE void width(RECT* r, u32 w);
INLINE void height(RECT* r, u32 h);
int contains(RECT* r, s32 x, s32 y);
int contains(RECT* r, POINT* pt);
int contains(RECT* r, RECT* op);
int intersects(RECT* r1, RECT* r2);

#define TOP       1  //x-axis -> right, y-axis v down
#define BOTTOM    2  //top is still up
#define RIGHT     4
#define LEFT      8
/* Determines which side of a rectangle the ray (first) intersects */
int intersect_side(RECT* r, LINE* ray);

/* FIXME: Additional shapes to be implemented when needed */

/* Inline definitions */
/* Point */
INLINE POINT point(s32 x, s32 y)
{  POINT pt = {x,y}; return pt; }

INLINE POINT add(POINT* src, POINT* op)
{  POINT dst; dst.x= src->x+op->x; dst.y= src->y+op->y; return dst;  }

INLINE POINT sub(POINT* dst, POINT* src, POINT* op)
{  POINT dst; dst.x= src->x-op->x; dst.y= src->y-op->y; return dst;  }

INLINE POINT neg(POINT* src)
{  POINT dst; dst.x= src->x*-1; dst.y= src->y*-1; return dst;  }

INLINE int dot(POINT* op1, POINT* op2)
{  return op1->x*op2->x+op1->y*op2->y; return dst;  }

INLINE POINT mult(POINT* dst, POINT* src, s32 op)
{  POINT dst; dst.x= src->x*op; dst.y= src->y*op; return dst;  }

INLINE POINT delta(POINT* dst, POINT* start, POINT* end)
{  POINT dst; dst.x= end->x-start->x; dst.y= end->y-start->y; return dst;  }

INLINE u32 magsq(POINT* pt)
{  return pt->x*pt->x+pt->y+pt->y;  }

/* Line */
INLINE LINE line(s32 x1, s32 y1, s32 x2, s32 y2)
{  LINE l = {{x1,y1},{x2,y2}}; return l;  }

INLINE LINE line(POINT* pt1, POINT* pt2)
{  LINE l; l.pt[0] = *pt1; l.pt[1] = *pt2; return l;  }

INLINE POINT delta(LINE* l)
{  POINT dst; dst.x= l->pt[1].x-l->pt[0].x; dst.y= l->pt[1].y-l->pt[0].y; 
      return dst;  }

/* Rectangle */
INLINE RECT rect(s32 x1, s32 y1, s32 x2, s32 y2)
{  RECT r = {{x1,y1},{x2,y2}}; return r;  }

INLINE RECT rect(POINT* pt1, POINT* pt2)
{  RECT r; r.pt[0] = *pt1; r.pt[1] = *pt2; return r;  }

INLINE u32 width(RECT* r)
{  return r->pt[1].x-r->pt[0].x;  }

INLINE u32 height(RECT* r)
{  return r->pt[1].y-r->pt[0].y;  }

INLINE void width(RECT* r, u32 w)
{  r->pt[1].x= r->pt[0].x+w;  }

INLINE void height(RECT* r, u32 h)
{  r->pt[1].y= r->pt[0].y+h;  }

#endif
