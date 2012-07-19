#include "mylib.h"
#include <debugging.h>
#include "field_0.h"

void load_gfx()
{
   for(int i=0; i<BACKTEST_HEIGHT; i++)
      for(int j=0; j<BACKTEST_WIDTH; j++)
         setPixel(j,i,backtest[i*BACKTEST_WIDTH + j]);
}

int main(void)
{



load_bitmap(p_bitmap);
load_music(p_song);
play_music();
state = 0;

while(1)
{
   poll_input();
   
   update_state(){
      switch input
      
   }
   
   vsync();
   
   update_graphics();
}








//	DEBUG_PRINT("Hello world!\n");
//	DEBUG_PRINTF("%#x\n",RGB(255,255,255));

int x = 10;
     while( x --> 0 ) // x goes to 0
     {
       DEBUG_PRINTF("%d ", x);
     }
     
     DEBUG_PRINT("\n");
	
	REG_DISPCNT = DCNT_MODE3 | DCNT_BG2;
	
	DEBUG_PRINTF("REG_DISPCNT = %#x\n",REG_DISPCNT);
	
	//make a border
	int clr = 31;
	
	for(int i=0; i<10; i++)
	{
		if(i%3 == 0)
			clr = 31;
		else if(i%3 == 1)
			clr = 15;
		else
			clr = 20;
		drawHollowRect(i,i,160-2*i,160-2*i,RGB15(clr,clr,clr));
	}
	
	
	//u32 bar = 0;
	//u32 red = 0;
	//u32 green = 0;
	//u32 blue = 0;
	
	//const u32 begin = 10;
	//const u32 width = 10;
	//const u32 height = 160 - 2*width;
	
	DEBUG_PRINTF("&backtest = %#x\n",(u32)backtest);
	
	load_gfx();
	
	/**
	//animate a simple picture
	while(1)
	{
	   vid_vsync();
	   
	   //animate
	   if(bar & 1){
	      drawRect(begin+(bar>>1)*width, begin, width, height, RGB15(red,green,blue) );
	   
	   
	   
	      red = (red+13)&0x1F;
	      green = (green+5)&0x1F;
	      blue = (blue+3)&0x1F;
	   }
	   
	   bar = (bar+1)%28;
	      
	   //paint a picture
	   
	   int begin = 10;
	   int bwidth = 10;
	
	   int r = 2;
	   int g = 0; 
	   int b = 30;
	
	   for(int i=begin; i<=160-2*begin; i+= bwidth)
      {
		   drawRect(i,begin,bwidth,160-2*begin,RGB15(r,g,b));
		   
		   r = (r+2)%32;
		   g = (g+5)%32;
		   b = (r+g+7)%32;
	   }
	   
	   
	   
	}**/
	
	return 0;
}


