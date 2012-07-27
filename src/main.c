#include <string.h>
#include <debugging.h>

#include "mylib.h"
#include "background.h"
#include "character.h"

#include "title.h"
#include "menu.h"

#include "bd_forest.h"
#include "bg_forest.h"

#include "pikmin_sheet.h"

#include "text.h"

OBJ_ATTR obj_buffer[128];
OBJ obj_array[10];

void title()
{
   //
   int* ptr;
   
   ptr = malloc(4);
   
   *ptr = 0x11223344;
   
   DEBUG_PRINTF("ptr = %#x\n", (u32)ptr);
   DEBUG_PRINTF("&obj_buffer = %#x\n",(u32)obj_buffer);
   
   u8 bytes[5] = { 0x11, 0x22, 0x33, 0x44, 0x55 };
   u16 halfwords[5] = { 0x1122, 0x3344, 0x5566, 0x7788, 0x99AA };
   u32 words[3] = { 0x11223344, 0x55667788, 0x99AABBCC };
   
   DEBUG_PRINTF("&bytes = %#x\n", (u32)bytes);
   DEBUG_PRINTF("&halfwords = %#x\n", (u32)halfwords);
   DEBUG_PRINTF("&words = %#x\n", (u32)words);
   
   
   

   memcpy(vid_mem, titleBitmap, titleBitmapLen);
   
   REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
   
   char* h = "PRESS A TO CONTINUE\n";
   
   int x = 50, y = 100;
   int frame = 0;
   while(~key_hit(KEY_A))
   {
      key_poll();
      vid_vsync();
      
      if( frame & 1 && *h != 0)
      {
         print_ch(*h, x, y, 0x0000);
         x += 6;
         h ++;
         frame = 0;
      }
      
      frame ++;
      
      if(key_hit(KEY_A))
         break;
   }
}

void menu()
{
   memcpy(vid_mem, menuBitmap, menuBitmapLen);
   
   while(~key_released(KEY_A))
   {
      key_poll();
      vid_vsync();
      
      if(key_hit(KEY_A))
         break;
   }
}

void init_obj_array(OBJ* obj, u32 num)
{
   OBJ_ATTR* oa = obj_buffer;
   while(num--)
   {
      obj->obj_buf = oa;
      obj++;
      oa++;
   }
}

void init_game()
{
   //Initialization
   
   //Field_0
   memcpy(pal_bg_mem, bd_forestPal, bd_forestPalLen);
   memcpy(&tile_mem[0][0], bd_forestTiles, bd_forestTilesLen);
   memcpy(&se_mem[30][0], bd_forestMap, bd_forestMapLen);
   
   REG_BG0CNT = BG_CBB(0) | BG_SBB(30) | BG_4BPP | BG_REG_32x32 | BG_PRIO(1);
   
   //Bg_Forest
   memcpy(&pal_bg_bank[1], bg_forestPal, bg_forestPalLen);
   memcpy(&tile_mem[0][16], bg_forestTiles, bg_forestTilesLen);
   memcpy(&se_mem[28][0], bg_forestMap, bg_forestMapLen);
   
   REG_BG1CNT = BG_CBB(0) | BG_SBB(28) | BG_4BPP | BG_REG_64x32 | BG_PRIO(0);
   
   
   memcpy(&tile8_mem[4][0], pikmin_sheetTiles, pikmin_sheetTilesLen);
   memcpy(pal_obj_mem, pikmin_sheetPal, pikmin_sheetPalLen);
	
	
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0 | DCNT_BG1 | DCNT_OBJ| DCNT_OBJ_1D;
	
	oam_init(obj_buffer, 128);
	
	u32 tid=0, pb=0;
	
	OBJ_ATTR *pkm = &obj_buffer[0];
	
	obj_set_attr(pkm, 
	             ATTR0_TALL, 
	             ATTR1_SIZE_16x32, 
	             ATTR2_PALBANK(pb) | tid);
	             
	pkm->attr0 |= ATTR0_8BPP;
	
	oam_copy(oam_mem, obj_buffer, 1);
}

int main(void)
{
   
   title();
   
   menu();
   
	init_game();
	
	int x=0, y=0;
	while(1)
	{
	   key_poll();
	   
	   x += key_tri_horz()*2;
	   y += key_tri_vert()*2;
	   
	   vid_vsync();
	   
	   //oam_copy(oam_mem, obj_buffer, 128);
	   
	   REG_BG1HOFS = x;
	   REG_BG1VOFS = y;
	}
	
	return 0;
}



















