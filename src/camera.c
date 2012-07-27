#include "camera.h"
#include "geometry.h"
#include "background.h"

RECT scr = { {0,0}, SCR_WIDTH, SCR_HEIGHT };

void update_camera(OBJ* target, RECT* bg, BG_REG* reg)
{
   POINT pt = target->pos;
   pt.x -= SCR_HALF_WIDTH;
   pt.y -= SCR_HALF_HEIGHT;
   
   scr.x = pt.x;
   scr.y = pt.y;
   
   //Align screen 
   if(scr.x < bg.x)
      scr.x = bg.x;
   if(scr.y < bg.y)
      scr.y = bg.y;
   if(scr.y+scr.h > bg.y+bg.h)
      scr.y = bg.y+bg.h-scr.h;
   if(scr.x+scr.w > bg.x+bg.w)
      scr.x = bg.x+bg.w-scr.w;
      
   //Find which SB the screen origin is in
   //FIXME: code is specific to 64x32 maps
   u32 sb = scr.x/8/32;
   
   //Update registers
   *reg++ = (*reg & (~BG_SBB_MASK)) | BG_SBB(sb);
   *reg++ = scr.x%(8*32);
   *reg = scr.y%(8*32);
}

void update_oam(OBJ* obj, u32 num)
{
   while(num--)
   {
      offsetTo(&obj->bb, &obj->pt);
      
      if(intersect(&scr, &obj->bb))
      {
         //Offset object
         u32 dx = obj->pt.x - scr->x;
         u32 dy = obj->pt.y - scr->y;
         
         u16* attr0 = &obj->obj_buf->attr0;
         u16* attr1 = &obj->obj_buf->attr1;
         
         *attr0 = (*attr0 & (~ATTR0_Y_MASK)) | (dy & ATTR0_Y_MASK);
         *attr1 = (*attr1 & (~ATTR0_Y_MASK)) | (dy & ATTR0_Y_MASK);
         
         *attr0 = (*attr0 & (~ATTR0_MODE_MASK)) | ATTR0_REG;
      }
      else
      {
         //Hide the object
         u16* attr0 = &obj->obj_buf->attr0;
         
         *attr0 = (*attr0 & (~ATTR0_MODE_MASK)) | ATTR0_HIDE;
      }
      
      obj++;
   }
}
