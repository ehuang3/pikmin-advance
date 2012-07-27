#include "shape.h"

/* Rectangle */
void offset(RECT* dst, RECT* op1, POINT* op2)
{  
   dst->pt[0]= op1->pt[0]+op2; 
   dst->pt[1]= op1->pt[1]+op2;  
}

void offsetTo(RECT* dst, RECT* op1, POINT* op2)
{  
   offset(dst,op1,neg(op1->pt[0])); 
   offset(dst,dst,op2);
}

int contains(RECT* r, s32 x, s32 y)
{
   return (x >= r->pt[0].x && x <= r->pt[1].x) &&
          (y >= r->pt[0].y && y <= r->pt[1].y);
}

int contains(RECT* r, POINT* pt)
{
   return contains(r, pt->x, pt->y);
}

int contains(RECT* r, RECT* p)
{
   return contains(r, p->pt[0].x, p->pt[0].y) &&
          contains(r, p->pt[1].x, p->pt[1].y) &&
          contains(r, p->pt[0].x, p->pt[1].y) &&
          contains(r, p->pt[1].x, p->pt[0].y);
}

int intersects(RECT* r1, RECT* r2)
{
   return contains(r1, r2->pt[0].x, r2->pt[0].y) ||
          contains(r1, r2->pt[1].x, r2->pt[1].y) ||
          contains(r1, r2->pt[0].x, r2->pt[1].y) ||
          contains(r1, r2->pt[1].x, r2->pt[0].y);
}

int intersect_side(RECT* r, LINE* ray)
{
   POINT d = delta(ray);
   
   //Normalize the signs
   if(d.x < 0)
      d = neg(&d);
   
   //Edge cases
   
   //
   POINT* start = &ray->pt[0];
   POINT* end = &ray->[1];
   
   //Assume start is outside
   //and end is inside
   
   //actually need to figure out which side of the object touched it first.
   //so for a rect I will need a corner to check ....
   
   
   
   
}



