#include "olimar.h"

c32 MAX_VELX = 3;
c32 MAX_VELY = 10;
c32 JUMP_VEL = 10;

typedef struct { u32 id,                  //Character data
                 RECT bb,
                 POINT vel,
                 u32 hp,
                 u32 atk,
                 u32 spd,
                 OBJ_ATTR* obj_buf,      //Object attribute data
                 LL_ROOT coll_cache,      //Collision data
                 void (*update)(void*),   //Functions
                 void (*animate)(void*),
                 void (*action_callback)(void*),
                 void* action_param
                } ALIGN4 OBJ;

void init_olimar(OLIMAR* o)
{
   o->bb = { 30,30,16,24 };
   o->hp = 10;
   o->update = update_olimar;
   o->animate = animate_olimar;
   o->coll_cache = { 0,0,0 };
   
   
   
   obj_set_attr(o->obj_buf, 
	             ATTR0_TALL, 
	             ATTR1_SIZE_32x64, 
	             ATTR2_PALBANK(0) | 0);
	             
	pkm->attr0 |= ATTR0_4BPP;
}

void update_olimar(OLIMAR* o)
{
   if(o->state & MOVE)
   {
      POINT* vel = &o->vel;
      vel->x += tri_bool_horz(); CLAMP(vel->x, MAX_VELX);
      if(vel->y != 0)
         vel->y += tri_bool_horz(); CLAMP(vel->y, MAX_VELY);
      
      if(vel->y == 0 && key_hit(KEY_A))
      {
         vel->y += JUMP_VEL;
      }
      
      if(vel->y == 0 && key_hit(KEY_B))
      {
         //transition to throw
      }
   
   }
}
