#include "mylib.h"
#include <debugging.h>


//==== Input

//! Repeated keys struct
typedef struct REPEAT_REC
{
	u16	keys;	//!< Repeated keys.
	u16	mask;	//!< Only check repeats for these keys.
	u8	count;	//!< Repeat counter.
	u8	delay;	//!< Limit for first repeat.
	u8	repeat;	//!< Limit for successive repeats.
} ALIGN4 REPEAT_REC;

u16 __key_curr= 0, __key_prev= 0;

REPEAT_REC __key_rpt= { 0, KEY_MASK, 60, 60, 30 };

// --------------------------------------------------------------------
// FUNCTIONS 
// --------------------------------------------------------------------


//! Poll for keystates and repeated keys
void key_poll(void)
{
	__key_prev= __key_curr;
	__key_curr= ~REG_KEYINPUT & KEY_MASK;

	REPEAT_REC *rpt= &__key_rpt;

	rpt->keys= 0;	// Clear repeats again

	if(rpt->delay)
	{
		// Change in masked keys: reset repeat
		// NOTE: this also counts as a repeat!
		if(key_transit(rpt->mask))
		{
			rpt->count= rpt->delay;
			rpt->keys= __key_curr;
		}
		else
			rpt->count--;

		// Time's up: set repeats (for this frame)
		if(rpt->count == 0)
		{
			rpt->count= rpt->repeat;
			rpt->keys= __key_curr & rpt->mask;
		}
	}
}

//! Wait until \a key is hit.
void key_wait_till_hit(u16 key)
{
	while(1)
	{
	   //TODO: Impement VBlankIntrWait()
		//VBlankIntrWait();
		key_poll();
		if(key_hit(key))
			return;
	}	
}

// === Repeated keys functions ===

//! Get status of repeated keys.
u32 key_repeat(u32 keys)
{
	return __key_rpt.keys & keys;
}

//! Set repeat mask. Only these keys will be considered for repeats.
void key_repeat_mask(u32 mask)
{
	__key_rpt.mask= mask & KEY_MASK;
}

//! Set the delay and repeat limits for repeated keys
/*!
	\param delay	Set first repeat limit. If 0, repeats are off.
	\param repeat	Sets later repeat limit.
	\note	Both limits have a range of [0, 255]. If either argument 
	  is <0, the old value will be kept.
*/
void key_repeat_limits(u32 delay, u32 repeat)
{
	REPEAT_REC *rpt= &__key_rpt;

	if(delay >= 0)
		rpt->delay= delay;
	if(repeat >= 0)
		rpt->repeat= repeat;

	rpt->count= delay;		// Reset counter.
}



//== Video functions

void vid_vsync()
{
   while(REG_VCOUNT >= 160)   // wait till VDraw
   { 
      //DEBUG_PRINTF("VBlank - %#x\n",REG_VCOUNT); 
   }
    
   while(REG_VCOUNT < 160)    // wait till VBlank
   { 
      //DEBUG_PRINTF("VDraw - %#x\n",REG_VCOUNT); 
   }
}

void setPixel(int x, int y, u16 color)
{
	vid_mem[y*VID_WIDTH+x]= color;
}

void drawRect(int x, int y, int width, int height, u16 color)
{
	for(int i=0; i<height; i++)
		for(int j=0; j<width; j++)
			setPixel(x+j,y+i,color);
}

void drawHollowRect(int x, int y, int width, int height, u16 color)
{
	drawRect(x,y,width,1,color);
	drawRect(x,y,1,height,color);
	drawRect(x+width-1,y,1,height,color);
	drawRect(x,y+height-1,width,1,color);
}
