#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "mylib.h"
#include "geometry.h"

typedef struct BG_DATA
{
   u32 w;
   u32 h;
   
} BG_DATA;

typedef struct REG_BG
{
  u16 bgcnt;
  u16 hofs;
  u16 vofs;
} ALIGN4 REG_BG;
               
//Macros

//Converts pixel value to tile index
#define tile(pix) ((pix)/8)

#define SCR_WIDTH 240;
#define SCR_HEIGHT 160;

#define SCR_HALF_WIDTH 120;
#define SCR_HALF_HEIGHT 80;

//Globals

REG_BG reg_bg_buffer[4];

//Functions

void reg_bg_copy(REG_BG *dst, const REG_BG *src, uint count);

//Returns screen-entry index of tile(x,y)
INLINE int se_index(u32 tx, u32 ty, u32 bgcnt)
{
   u32 sb = tx/32;
   
   if((bgcnt & BG_SIZE_MASK) == BG_REG_32x64)
      sb += ty/32;
   if((bgcnt & BG_SIZE_MASK) == BG_REG_64x64)
      sb += ty/64;
   
   return sb*1024 + tx%32 + ty%32;
}

//Returns screen-entry address of tile(x,y)
INLINE SCR_ENTRY* se_addr(u32 tx, u32 ty, u32 bgcnt)
{
   return &map_mem[se_index(tx,ty,bgcnt)];
}

#endif
