/**
 * CS 2110 - Summer 2012 - Homework #11
 * Edited by: Brandon Whitehead
 *
 * list.c: Complete the functions!
 **/

#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/* The node struct.  Has a prev pointer, next pointer, and data. */
/* DO NOT DEFINE ANYTHING OTHER THAN WHAT'S GIVEN OR YOU WILL GET A ZERO*/
/* Design consideration only this file should know about nodes */
/* Only this file should be manipulating nodes */
/* DO NOT TOUCH THIS DECLARATION DO NOT PUT IT IN OTHER FILES */
typedef struct lnode
{
  struct lnode* prev; /* Pointer to previous node */
  struct lnode* next; /* Pointer to next node */
  void* data; /* User data */
} node;


/* Do not create any global variables here. Your linked list library should obviously work for multiple linked lists */
// This function is declared as static since you should only be calling this inside this file.
static node* create_node(void* data);

/** create_list
  *
  * Creates a list by allocating memory for it on the heap.
  * Be sure to initialize size to zero and head/tail to NULL.
  *
  * @return an empty linked list
  */
list* create_list(void)
{
    list* l = malloc(list);
    l->head = 0;
    l->tail = 0;
    l->size = 0;
    return l;
}

/** create_node
  *
  * Helper function that creates a node by allocating memory for it on the heap.
  * Be sure to set its pointers to NULL.
  *
  * @param data a void pointer to data the user wants to store in the list
  * @return a node
  */
static node* create_node(void* data)
{
    node* nd = malloc(sizeof node);
    nd->data = data;
    nd->prev = 0;
    nd->next = 0;
    return nd;
}

/** push_front
  *
  * Adds the data to the front of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_front(list* llist, void* data)
{
   node* nd = create_node(data);

   nd->next = llist->head;
   llist->head->prev = nd;
   llist->head = nd;

   if(!llist->tail)
      llist->tail = nd;

   llist->size++;
}

/** push_back
  *
  * Adds the data to the back/end of the linked list
  *
  * @param llist a pointer to the list.
  * @param data pointer to data the user wants to store in the list.
  */
void push_back(list* llist, void* data)
{
   node* nd = create_node(data);

   nd->prev = llist->tail;
   llist->tail->next = nd;
   llist->tail = nd;

   if(!llist->head)
      llist->head = nd;

   llist->size++;
}

/** remove_front
  *
  * Removes the node at the front of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed (which is only there are no elements) 0 if the remove succeeded.
  */
int remove_front(list* llist, list_op free_func)
{
   if(!llist->size)
      return -1;

   free_func(llist->head->data);

   node* nd = llist->head;
   llist->head = nd->next;
   
   llist->head->prev = 0;
   
   llist->size--;

   free(nd);
}

/** remove_back
  *
  * Removes the node at the back of the linked list
  *
  * @warning Note the data the node is pointing to is also freed. If you have any pointers to this node's data it will be freed!
  *
  * @param llist a pointer to the list.
  * @param free_func pointer to a function that is responsible for freeing the node's data.
  * @return -1 if the remove failed 0 if the remove succeeded.
  */
int remove_back(list* llist, list_op free_func)
{
    if(llist->size == 0)
      return -1;
      
    free_func(llist->tail->data);
    
    node* nd = llist->tail;
    llist->tail = nd->prev;
    
    llist->tail->next = 0;
    
    llist->size--;
    
    free(nd);
}

/** remove_if
  *
  * Removes all nodes whose data when passed into the predicate function returns true
  *
  * @param llist a pointer to the list
  * @param pred_func a pointer to a function that when it returns true it will remove the element from the list and do nothing otherwise @see list_pred.
  * @param free_func a pointer to a function that is responsible for freeing the node's data
  * @return the number of nodes that were removed.
  */
int remove_if(list* llist, list_pred pred_func, list_op free_func)
{
   int num = llist->size;
   int count = 0;

   node* nd = llist->head;

   while(num--)
   {
      if(pred_func(nd->data))
      {
         free_func(nd->data);
         
         if(nd == llist->head)
            llist->head = nd->next;
         if(nd == llist->tail)
            llist->tail = nd->prev;
         
         if(nd->prev)
            nd->prev->next = nd->next;
         if(nd->next)
            nd->next->prev = nd->prev;
            
         free(nd);
         
         count++;
         llist->size--;
      }
      n = n->next;
   }

   return count;
}

/** front
  *
  * Gets the data at the front of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the first node in the linked list or NULL.
  */
void* front(list* llist)
{
   if(llist->size == 0)
      return 0;
   return llist->head->data;
}

/** back
  *
  * Gets the data at the "end" of the linked list
  * If the list is empty return NULL.
  *
  * @param llist a pointer to the list
  * @return The data at the last node in the linked list or NULL.
  */
void* back(list* llist)
{
   if(llist->size == 0)
      return 0;
   return llist->tail->data;
}

/** is_empty
  *
  * Checks to see if the list is empty.
  *
  * @param llist a pointer to the list
  * @return 1 if the list is indeed empty 0 otherwise.
  */
int is_empty(list* llist)
{
    return llist->size > 0;
}

/** size
  *
  * Gets the size of the linked list
  *
  * @param llist a pointer to the list
  * @return The size of the linked list
  */
int size(list* llist)
{
    return llist->size;
}

/** empty_list
  *
  * Empties the list after this is called the list should be empty.
  *
  * @param llist a pointer to a linked list.
  * @param free_func function used to free the node's data.
  *
  */
void empty_list(list* llist, list_op free_func)
{
   node* nd = llist->head;
   while(llist->size--)
   {
      free_func(nd->data);
      free(nd);
      nd = nd->next;
   }
   llist->head = 0;
   llist->tail = 0;
}

/** traverse
  *
  * Traverses the linked list calling a function on each node's data.
  *
  * @param llist a pointer to a linked list.
  * @param do_func a function that does something to each node's data.
  */
void traverse(list* llist, list_op do_func)
{
   node* nd = llist->head;
   int num = llist->size;
   while(num--)
   {
      do_func(nd->data);
      nd = nd->next;
   }
}

