#include "background.h"


void reg_bg_copy(REG_BG *dst, const REG_BG *src, uint count)
{
   #if 1
       while(count--)
           *dst++ = *src++;
   #else
       u32 *dstw= (u32*)dst, *srcw= (u32*)src;
       while(count--)
       {
           *dstw++ = *srcw++;
           *dstw++ = *srcw++;
       }
   #endif
}
