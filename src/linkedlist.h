#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include <stdlib.h>

#include "mylib.h"

#define LL_NODE(n) ((LL_NODE*)n)

typedef struct LL_NODE { void* obj;
                 void* next;
                 void* prev;
               } LL_NODE;
               
typedef struct LL_ROOT { void* obj;
                 void* next;
                 void* last;
               } LL_ROOT;
               
INLINE void insert(LL_ROOT* rt, LL_NODE* nd)
{
   if(rt->next == 0)
      rt->next = nd;
      
   LL_NODE(rt->last)->next = nd;
   nd->prev = rt->last;
   rt->last = nd;
}

//Deletes single node from list/memory
INLINE void delete(LL_ROOT* rt, LL_NODE* nd)
{
   LL_NODE(nd->prev)->next = nd->next;
   LL_NODE(nd->next)->prev = nd->prev;
   
   if(rt->last == nd)
      rt->last = nd->prev;
      
   free(nd);
}

//Deletes all nodes and data from dynamic memory, except for root
INLINE void clear(LL_ROOT* rt)
{
   if(rt->last == 0)
      return;   
   
   LL_NODE* cur = rt->last;
   LL_NODE* prev = cur->prev;
   
   while((u32)cur != (u32)rt)
   {
      free(cur->obj);
      free(cur);
      cur = prev;
      prev = cur->prev;
   }
}

#endif
