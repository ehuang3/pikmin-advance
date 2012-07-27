#ifndef COLLISION_H
#define COLLISION_H

#include "mylib.h"
#include "shape.h"

//Typedefs
struct COLL_SHAPE;

typedef struct COLL_OBJ 
{
   POINT pos;
   POINT vel;
   u32 mass;
   struct COLL_SHAPE* coll_shape;
   u32 coll_mask;
   u32 coll_type;
   void* coll_cache;
   void* user_ptr;
   void (*user_callback)(void*);
} ALIGN4 COLL_OBJ;
#define COLL_OBJ_BYTE_SIZE 10*4;

typedef struct COLL_SHAPE
{
   u32 shape_type;
   void* shape;
   RECT* aabb;
} ALIGN4 COLL_SHAPE;
#define COLL_SHAPE_BYTE_SIZE 3*4;

typedef struct COLL_PAIR_CACHE
{
   COLL_OBJ* obj1;
   COLL_OBJ* obj2;
} COLL_PAIR_CACHE;

/* A function pointer type that points to a function that takes in a void* and returns nothing call it coll_op */
typedef void (*coll_op)(void*);
/* A function pointer type that points to a function that takes in a const void* and returns an int call it coll_pred */
typedef int (*coll_pred)(const void*);


//Prototypes
/* Creation, deletion of COLL_SHAPE's */
COLL_SHAPE* create_collshape(u32 type, void* shape);
void free_collshape(COLL_SHAPE* coll_shape);
void calc_aabb(COLL_SHAPE* coll_shape);

/* Creation, deletion of COLL_OBJ's from the engine */
int add_collobj(COLL_OBJ* coll_obj);
COLL_OBJ* create_collobj(POINT* pos, POINT* vel, u32 mass, COLL_SHAPE* shape);
void remove_collobj(COLL_OBJ* coll_obj);

/* Simple rectangle collision against background and special squares */
void hwk11_collision(list* hwk11_objs);
void do_nothing(void* data); //Hack for manipulating linked lists :P

/* Collision detection */
void aabb_sweep(int x_min, int x_max);

void rect_rect_alg(COLL_OBJ* obj1, COLL_OBJ* obj2);





void detect_collisions(COLL_OBJ* obj, u32 num);

void tilemap_collision(COLL_OBJ* obj, REG_BG* reg);

void obj_pair_collision(COLL_OBJ* obj1, COLL_OBJ* obj2);

void add_collision(COLL_OBJ* obj, u32 tx, u32 ty);

void add_collision(COLL_OBJ* obj1, COLL_OBJ* obj2);

#endif
