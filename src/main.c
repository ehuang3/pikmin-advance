#include <string.h>

#include "mylib.h"
#include <debugging.h>
#include "field_0.h"


int main(void)
{
   
   memcpy(pal_bg_mem, field_0Pal, field_0PalLen);
   memcpy(&tile8_mem[0][0], field_0Tiles, field_0TilesLen);
   memcpy(&se_mem[30][0], field_0Map, field_0MapLen);
	
	REG_BG0CNT = BG_CBB(0) | BG_SBB(30) | BG_8BPP | BG_REG_32x32;
	REG_DISPCNT = DCNT_MODE0 | DCNT_BG0;
	
	int x=0, y=0;
	while(1)
	{
	   vid_vsync();
	   key_poll();
	   
	   x += key_tri_horz();
	   y += key_tri_vert();
	   
	   REG_BG0HOFS = x;
	   REG_BG0VOFS = y;
	
	}
	
	return 0;
}



















