#ifndef CHARACTER_H
#define CHARACTER_H

#include "mylib.h"
#include "linkedlist.h"



typedef struct { u32 id;                  //Character data
                 POINT pos;
                 POINT vel;
                 u32 hp;
                 u32 atk;
                 u32 spd;
                 OBJ_ATTR* obj_buf;      //Object attribute data
                 LL_ROOT coll_cache;      //Collision data
                 void (*update)(void*);   //Functions
                 void (*animate)(void*);
                 void (*action_callback)(void*);
                 void* action_param;
                } ALIGN4 OBJ;
                                
#endif
