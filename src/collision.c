#include "collision.h"
#include "linkedlist.h"

#include <stdlib.h>


/* Array of COLL_OBJ*'s for physics simulation */
#define MAX_COLL_OBJS 128
COLL_OBJ* _collObjs[MAX_COLL_OBJS];
u32 numCollObjs = 0;

/* Collision shape */
COLL_SHAPE* create_collshape(u32 type, void* shape)
{
   COLL_SHAPE* collshape = malloc(COLL_SHAPE_BYTE_SIZE);
   collshape->shape_type = type;
   collshape->shape = shape;
   calc_aabb(collshape);
}

void free_collshape(COLL_SHAPE* collshape)
{
   //Free in reverse order
   u32 type = collshape->type;
   //Delete aabb
   if(type & RECT_SHAPE)
      //Do nothing as aabb points to collshape->shape
   //Delete shape
   if(type & RECT_SHAPE)
      free(collshape->shape);
   //Delete COLL_SHAPE
   free(collshape);
}

void calc_aabb(COLL_SHAPE* collshape)
{
   u32 type = collshape->shape_type;
   if(type & RECT_SHAPE)
      collshape->aabb = collshape->shape;
}


/* Collision object */
COLL_OBJ* create_collobj(POINT* pos, POINT* vel, u32 mass, COLL_SHAPE* shape)
{
   COLL_OBJ* obj = malloc(COLL_OBJ_BYTE_SIZE);
   obj->pos = *pos;
   obj->vel = *vel;
   obj->mass = mass;
   obj->coll_shape = shape;
   
}

void free_collobj(COLL_OBJ* coll_obj)
{
   //Free in reverse order of creation
   free_collshape(coll_obj->coll_shape);
   free(coll_obj);
}

int add_collobj(COLL_OBJ* coll_obj)
{
   int num = MAX_COLL_OBJS;
   COLL_OBJ** pp_co = _collObjs;
   while(num--)
   {
      if(!*pp_co)
      {
         *pp_co = coll_obj;
         return 1;
      }
      pp_co++;
   }
   return 0;
}

int remove_collobj(COLL_OBJ* coll_obj);
{
   int num = MAX_COLL_OBJS;
   COLL_OBJ** pp_co = _collObjs;
   while(num--)
   {
      if(*pp_co == coll_obj)
      {
         free_collobj(coll_obj);
         *pp_co = 0;
         return 1;
      }
      pp_co++;
   }
   return 0;
}


/* Hwk11 collision stuff */
void hwk11_collision(list* hwk11_objs)
{
   while(!is_empty(hwk11_objs))
   {
      COLL_OBJ* obj = front(hwk11_objs);
      RECT* r1 = obj->coll_shape->shape;
      
      //Test against rectangles in world
      for(int i=0; i<MAX_COLL_OBJS; i++)
      {
         if(_collObjs[i])
         {
            RECT* r2 = (*_collObjs[i])->coll_shape->shape;
            if(intersects(r1,r2))
            {
               //Callback for special effects
               obj->usr_callback(_collObjs[i]);
            }
         }
      }
      //Remove front node while keeping the data intact
      remove_front(hwk11_objs, do_nothing); //stupid linked list implementation
   }
}











/* Collision detection */
list* aabb_sweep()
{
   
}









//Assume rect rect collision
//Want physics!!! like bouncing
solve_constraints(COLL_OBJ* obj1, COLL_OBJ* obj2)
{
   
}





void detect_collisions(COLL_OBJ* obj, u32 num)
{
   u32 count = num;
   COLL_OBJ* coa = obj;   //Store for pairwise collision

   while(count--)
   {
      tilemap_collision(obj++, reg_bg_buffer[COLL_BG]);
   }
   
   //Slower non-pointer version
   for(int i=0; i<num; i++)
      for(int j=0; j<i; j++)
         obj_pair_collision(&coa[i],&coa[j]);
}

void tilemap_collision(COLL_OBJ* obj, REG_BG* reg)
{
   u16 bgcnt = reg->bgcnt;
   
   RECT* bb = &obj->bb; //Get bounding box
   
   POINT pt;
   pt.x = reg->hofs + obj->pos.x + bb->pt.x;
   pt.y = reg->vofs + obj->pos.y + bb->pt.y;
   
   //Starting tile of bounding box
   u32 tx = pt.x/8;
   u32 ty = pt.y/8;
   
   //Calculate width and height in tiles
   u32 d_tx = bb->w/8 + (pt.x%8 ? 1:0);
   u32 d_ty = bb->h/8 + (pt.y%8 ? 1:0);
   u32 dt = d_tx;
   
   while(d_ty--)
   {
      while(dt--)
      {
         if(*se_addr(tx, ty, bgcnt)) //Tile is non-empty
         {
            add_collision(obj, tx, ty);
         }
         tx++;
      }
      d = d_tx;
      tx = pt.x/8;
      ty++;
   }
}

void obj_pair_collision(COLL_OBJ* obj1, COLL_OBJ* obj2)
{
   RECT r1 = obj1->bb;
   RECT r2 = obj2->bb;
   
   translate(&r1, &obj1->pos);
   translate(&r2, &obj2->pos);
   
   if(intersect(&r1, &r2))
      add_collision(obj1, obj2);
}

void add_collision(COLL_OBJ* obj, u32 tx, u32 ty)
{
   COLL_HIT* coll = malloc(sizeof(COLL_HIT));
   coll->pt.x = tx;
   coll->pt.y = ty;
   
   LL_NODE* node = malloc(sizeof(LL_NODE));
   node->obj = coll;
   
   insert(obj->coll_cache, node);
}

void add_collision(COLL_OBJ* obj1, COLL_OBJ* obj2)
{
   COLL_HIT* coll1 = malloc(sizeof(COLL_HIT));
   COLL_HIT* coll2 = malloc(sizeof(COLL_HIT));
   
   coll1->obj = obj2;
   coll2->obj = obj1;
   
   coll1->pt = {0,0};
   coll2->pt = {0,0};
   
   LL_NODE* node1 = malloc(sizeof(LL_NODE));
   LL_NODE* node2 = malloc(sizeof(LL_NODE));
   
   node1->obj = coll1;
   node2->obj = coll2;
   
   insert(obj1->coll_cache, node1);
   insert(obj2->coll_cache, node2);
}
