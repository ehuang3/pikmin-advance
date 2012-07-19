//== mylib.h

#ifndef MYLIB_H
#define MYLIB_H

//== Typedefs

typedef unsigned char 	u8;
typedef unsigned short 	u16;
typedef unsigned int 	u32, uint;

typedef signed char     s8;
typedef signed short    s16;
typedef signed int      s32;

typedef volatile unsigned char   vu8;
typedef volatile unsigned short  vu16;
typedef volatile unsigned int    vu32;

// Secondary typedefs

typedef s32 FIXED;					//!< Fixed point type
typedef u16 COLOR;					//!< Type for colors
typedef u16 SCR_ENTRY, SE;			//!< Type for screen entries
typedef u8  SCR_AFF_ENTRY, SAE;		//!< Type for affine screen entries

//! 4bpp tile type, for easy indexing and copying of 4-bit tiles
typedef struct { u32 data[8];  } TILE, TILE4;

//! 8bpp tile type, for easy indexing and 8-bit tiles
typedef struct { u32 data[16]; } TILE8;

//! Palette bank type, for 16-color palette banks 
typedef COLOR PALBANK[16];

/*! \name VRAM array types
*	These types allow VRAM access as arrays or matrices in their 
*	  most natural types.
*/

typedef SCR_ENTRY	SCREENLINE[32];
typedef SCR_ENTRY	SCREENMAT[32][32];
typedef SCR_ENTRY	SCREENBLOCK[1024];

typedef COLOR		M3LINE[240];
typedef u8			M4LINE[240];	// NOTE: u8, not u16!!
typedef COLOR		M5LINE[160];

typedef TILE		CHARBLOCK[512];
typedef TILE8		CHARBLOCK8[256];

// Macros

#define INLINE static inline

//! Put variable in IWRAM (default).
#define IWRAM_DATA __attribute__((section(".iwram")))

//! Put variable in EWRAM.
#define EWRAM_DATA __attribute__((section(".ewram")))

//! Put <b>non</b>-initialized variable in EWRAM.
#define  EWRAM_BSS __attribute__((section(".sbss")))

//! Put function in IWRAM.
#define IWRAM_CODE __attribute__((section(".iwram"), long_call))

//! Put function in EWRAM.
#define EWRAM_CODE __attribute__((section(".ewram"), long_call))

//! Force a variable to an \a n-byte boundary
#define ALIGN(n)	__attribute__((aligned(n)))

//! Force word alignment.
#define ALIGN4		__attribute__((aligned(4)))

//== Structs

typedef struct
{
   const volatile void *src;
   volatile void *dst;
   volatile unsigned int cnt;
} DMA_REC;

//==== Memory

#define MEM_EWRAM	0x02000000	//!< External work RAM
#define MEM_IWRAM	0x03000000	//!< Internal work RAM
#define MEM_IO		0x04000000	//!< I/O registers
#define MEM_PAL	0x05000000	//!< Palette. Note: no 8bit write !!
#define MEM_VRAM	0x06000000	//!< Video RAM. Note: no 8bit write !!
#define MEM_OAM	0x07000000	//!< Object Attribute Memory (OAM) Note: no 8bit write !!
#define MEM_ROM	0x08000000	//!< ROM. No write at all (duh)
#define MEM_SRAM	0x0E000000	//!< Static RAM. 8bit write only

//== Sections Sizes

#define EWRAM_SIZE	0x40000
#define IWRAM_SIZE	0x08000
#define PAL_SIZE	   0x00400
#define VRAM_SIZE	   0x18000
#define OAM_SIZE	   0x00400
#define SRAM_SIZE	   0x10000

#define PAL_BG_SIZE		0x00200		//!< BG palette size
#define PAL_OBJ_SIZE	   0x00200		//!< Object palette size
#define CBB_SIZE		   0x04000		//!< Charblock size
#define SBB_SIZE		   0x00800		//!< Screenblock size
#define VRAM_BG_SIZE	   0x10000		//!< BG VRAM size
#define VRAM_OBJ_SIZE	0x08000		//!< Object VRAM size
#define M3_SIZE			0x12C00		//!< Mode 3 buffer size
#define M4_SIZE			0x09600		//!< Mode 4 buffer size
#define M5_SIZE			0x0A000		//!< Mode 5 buffer size
#define VRAM_PAGE_SIZE	0x0A000		//!< Bitmap page size

//== Subsections of Memory

#define MEM_PAL_BG		(MEM_PAL)					   //!< Background palette address
#define MEM_PAL_OBJ		(MEM_PAL + PAL_BG_SIZE)		//!< Object palette address
#define MEM_VRAM_FRONT	(MEM_VRAM)					   //!< Front page address
#define MEM_VRAM_BACK	(MEM_VRAM + VRAM_PAGE_SIZE)//!< Back page address
#define MEM_VRAM_OBJ	   (MEM_VRAM + VRAM_BG_SIZE)	//!< Object VRAM address

//== Memory Map

//! Background palette.
/*! pal_bg_mem[i]	= color i					( COLOR )
*/
#define pal_bg_mem		((COLOR*)MEM_PAL)

//! Object palette. 
/*! pal_obj_mem[i]	= color i					( COLOR )
*/
#define pal_obj_mem		((COLOR*)MEM_PAL_OBJ)


//! Background palette matrix. 
/*! pal_bg_bank[y]		= bank y				( COLOR[ ] )<br>
	pal_bg_bank[y][x]	= color color y*16+x	( COLOR )
*/
#define pal_bg_bank		((PALBANK*)MEM_PAL)

//! Object palette matrix. 
/*!	pal_obj_bank[y]		= bank y				( COLOR[ ] )<br>
	pal_obj_bank[y][x]	= color y*16+x			( COLOR )
*/
#define pal_obj_bank	((PALBANK*)MEM_PAL_OBJ)

//!	Charblocks, 4bpp tiles.
/*!	tile_mem[y]		= charblock y				( TILE[ ] )<br>
	tile_mem[y][x]	= block y, tile x			( TILE )
*/
#define tile_mem		( (CHARBLOCK*)MEM_VRAM)

//!	Charblocks, 8bpp tiles.
/*!	tile_mem[y]		= charblock y				( TILE[ ] )<br>
	tile_mem[y][x]	= block y, tile x			( TILE )
*/
#define tile8_mem		((CHARBLOCK8*)MEM_VRAM)

//!	Object charblocks, 4bpp tiles.
/*!	tile_mem[y]		= charblock y				( TILE[ ] )<br>
	tile_mem[y][x]	= block y, tile x			( TILE )
*/
#define tile_mem_obj	( (CHARBLOCK*)MEM_VRAM_OBJ)

//!	Object charblocks, 4bpp tiles.
/*!	tile_mem[y]		= charblock y				( TILE[ ] )<br>
	tile_mem[y][x]	= block y, tile x			( TILE )
*/
#define tile8_mem_obj	((CHARBLOCK8*)MEM_VRAM_OBJ)

//! Screenblocks as arrays
/*!	se_mem[y]		= screenblock y				( SCR_ENTRY[ ] )<br>
*	se_mem[y][x]	= screenblock y, entry x	( SCR_ENTRY )
*/
#define se_mem			((SCREENBLOCK*)MEM_VRAM)


//! Screenblock as matrices
/*!	se_mat[s]		= screenblock s					( SCR_ENTRY[ ][ ] )<br>
	se_mat[s][y][x]	= screenblock s, entry (x,y)	( SCR_ENTRY )
*/
#define se_mat			((SCREENMAT*)MEM_VRAM)

//! Main mode 3/5 frame as an array
/*!	vid_mem[i]		= pixel i						( COLOR )
*/
#define vid_mem			((COLOR*)MEM_VRAM)

//! Mode 3 frame as a matrix
/*!	m3_mem[y][x]	= pixel (x, y)					( COLOR )
*/
#define m3_mem			((M3LINE*)MEM_VRAM)


//! Mode 4 first page as a matrix
/*!	m4_mem[y][x]	= pixel (x, y)					( u8 )
*	\note	This is a byte-buffer. Not to be used for writing.
*/
#define m4_mem			((M4LINE*)MEM_VRAM)

//! Mode 5 first page as a matrix
/*!	m5_mem[y][x]	= pixel (x, y)					( COLOR )
*/
#define m5_mem			((M5LINE*)MEM_VRAM)

//! First page array
#define vid_mem_front	((COLOR*)MEM_VRAM)

//! Second page array
#define vid_mem_back	((COLOR*)MEM_VRAM_BACK)

//! Mode 4 second page as a matrix
/*!	m4_mem[y][x]	= pixel (x, y)					( u8 )
*	\note	This is a byte-buffer. Not to be used for writing.
*/
#define m4_mem_back		((M4LINE*)MEM_VRAM_BACK)

//! Mode 5 second page as a matrix
/*!	m5_mem[y][x]	= pixel (x, y)					( COLOR )
*/
#define m5_mem_back		((M5LINE*)MEM_VRAM_BACK)

//! Object attribute memory
/*!	oam_mem[i]		= object i						( OBJ_ATTR )
*/
#define oam_mem			((OBJ_ATTR*)MEM_OAM)
#define obj_mem			((OBJ_ATTR*)MEM_OAM)

//! Object affine memory
/*!	obj_aff_mem[i]		= object matrix i			( OBJ_AFFINE )	
*/
#define obj_aff_mem		((OBJ_AFFINE*)MEM_OAM)

//! ROM pointer
#define rom_mem			((u16*)MEM_ROM)

//! SRAM pointer
#define sram_mem		((u8*)MEM_SRAM)

#define VID_WIDTH 240
#define VID_HEIGHT 160

//== Register List

#define REG_BASE		   MEM_IO

// Display registers
#define REG_DISPCNT		*(vu32*)(REG_BASE+0x0000)	//!< Display control
#define REG_DISPSTAT		*(vu16*)(REG_BASE+0x0004)	//!< Display status
#define REG_VCOUNT		*(vu16*)(REG_BASE+0x0006)	//!< Scanline count

// Background control registers
#define REG_BGCNT			((vu16*)(REG_BASE+0x0008))	//!< Bg control array

#define REG_BG0CNT			*(vu16*)(REG_BASE+0x0008)	//!< Bg0 control
#define REG_BG1CNT			*(vu16*)(REG_BASE+0x000A)	//!< Bg1 control
#define REG_BG2CNT			*(vu16*)(REG_BASE+0x000C)	//!< Bg2 control
#define REG_BG3CNT			*(vu16*)(REG_BASE+0x000E)	//!< Bg3 control

// Regular background scroll registers. (write only!)
#define REG_BG_OFS			((BG_POINT*)(REG_BASE+0x0010))	//!< Bg scroll array

#define REG_BG0HOFS			*(vu16*)(REG_BASE+0x0010)		//!< Bg0 horizontal scroll
#define REG_BG0VOFS			*(vu16*)(REG_BASE+0x0012)		//!< Bg0 vertical scroll
#define REG_BG1HOFS			*(vu16*)(REG_BASE+0x0014)		//!< Bg1 horizontal scroll
#define REG_BG1VOFS			*(vu16*)(REG_BASE+0x0016)		//!< Bg1 vertical scroll
#define REG_BG2HOFS			*(vu16*)(REG_BASE+0x0018)		//!< Bg2 horizontal scroll
#define REG_BG2VOFS			*(vu16*)(REG_BASE+0x001A)		//!< Bg2 vertical scroll
#define REG_BG3HOFS			*(vu16*)(REG_BASE+0x001C)		//!< Bg3 horizontal scroll
#define REG_BG3VOFS			*(vu16*)(REG_BASE+0x001E)		//!< Bg3 vertical scroll

// DMA registers

#define REG_DMA	      ((volatile DMA_REC*)(REG_BASE+0x00B0))	//!< DMA as DMA_REC array

#define REG_DMA0SAD		*(vu32*)(REG_BASE+0x00B0)	//!< DMA 0 Source address
#define REG_DMA0DAD		*(vu32*)(REG_BASE+0x00B4)	//!< DMA 0 Destination address
#define REG_DMA0CNT		*(vu32*)(REG_BASE+0x00B8)	//!< DMA 0 Control

#define REG_DMA1SAD		*(vu32*)(REG_BASE+0x00BC)	//!< DMA 1 Source address
#define REG_DMA1DAD		*(vu32*)(REG_BASE+0x00C0)	//!< DMA 1 Destination address
#define REG_DMA1CNT		*(vu32*)(REG_BASE+0x00C4)	//!< DMA 1 Control

#define REG_DMA2SAD		*(vu32*)(REG_BASE+0x00C8)	//!< DMA 2 Source address
#define REG_DMA2DAD		*(vu32*)(REG_BASE+0x00CC)	//!< DMA 2 Destination address
#define REG_DMA2CNT		*(vu32*)(REG_BASE+0x00D0)	//!< DMA 2 Control

#define REG_DMA3SAD		*(vu32*)(REG_BASE+0x00D4)	//!< DMA 3 Source address
#define REG_DMA3DAD		*(vu32*)(REG_BASE+0x00D8)	//!< DMA 3 Destination address
#define REG_DMA3CNT		*(vu32*)(REG_BASE+0x00DC)	//!< DMA 3 Control

// Keypad registers

#define REG_KEYINPUT		*(vu16*)(REG_BASE+0x0130)	//!< Key status
#define REG_KEYCNT		*(vu16*)(REG_BASE+0x0132)	//!< Key IRQ control

// Interrupt / System registers

#define REG_IE				*(vu16*)(REG_BASE+0x0200)	//!< IRQ enable
#define REG_IF				*(vu16*)(REG_BASE+0x0202)	//!< IRQ status/acknowledge
#define REG_WAITCNT		*(vu16*)(REG_BASE+0x0204)	//!< Waitstate control
#define REG_IME			*(vu16*)(REG_BASE+0x0208)	//!< IRQ master enable
#define REG_PAUSE			*(vu16*)(REG_BASE+0x0300)	//!< Pause system (?)

//==== Control flags

//== REG_DISPCNT
#define DCNT_MODE0			     0	//!< Mode 0; bg 0-4: reg
#define DCNT_MODE1			0x0001	//!< Mode 1; bg 0-1: reg; bg 2: affine
#define DCNT_MODE2			0x0002	//!< Mode 2; bg 2-3: affine
#define DCNT_MODE3			0x0003	//!< Mode 3; bg2: 240x160\@16 bitmap
#define DCNT_MODE4			0x0004	//!< Mode 4; bg2: 240x160\@8 bitmap
#define DCNT_MODE5			0x0005	//!< Mode 5; bg2: 160x128\@16 bitmap

// layers
#define DCNT_BG0			   0x0100	//!< Enable bg 0
#define DCNT_BG1			   0x0200	//!< Enable bg 1
#define DCNT_BG2			   0x0400	//!< Enable bg 2
#define DCNT_BG3			   0x0800	//!< Enable bg 3
#define DCNT_OBJ			   0x1000	//!< Enable objects

//== REG_BGxCNT
#define BG_MOSAIC		0x0040	//!< Enable Mosaic
#define BG_4BPP				 0	//!< 4bpp (16 color) bg (no effect on affine bg)
#define BG_8BPP			0x0080	//!< 8bpp (256 color) bg (no effect on affine bg)
#define BG_WRAP			0x2000	//!< Wrap around edges of affine bgs
#define BG_SIZE0			 0
#define BG_SIZE1		0x4000
#define BG_SIZE2		0x8000
#define BG_SIZE3		0xC000
#define BG_REG_32x32		 0	//!< reg bg, 32x32 (256x256 px)
#define BG_REG_64x32	0x4000	//!< reg bg, 64x32 (512x256 px)
#define BG_REG_32x64	0x8000	//!< reg bg, 32x64 (256x512 px)
#define BG_REG_64x64	0xC000	//!< reg bg, 64x64 (512x512 px)
#define BG_AFF_16x16		 0	//!< affine bg, 16x16 (128x128 px)
#define BG_AFF_32x32	0x4000	//!< affine bg, 32x32 (256x256 px)
#define BG_AFF_64x64	0x8000	//!< affine bg, 64x64 (512x512 px)
#define BG_AFF_128x128	0xC000	//!< affine bg, 128x128 (1024x1024 px)

#define BG_PRIO_MASK	0x0003
#define BG_PRIO_SHIFT		 0
#define BG_PRIO(n)		((n)<<BG_PRIO_SHIFT)

#define BG_CBB_MASK		0x000C
#define BG_CBB_SHIFT		 2
#define BG_CBB(n)		((n)<<BG_CBB_SHIFT)

#define BG_SBB_MASK		0x1F00
#define BG_SBB_SHIFT		 8
#define BG_SBB(n)		((n)<<BG_SBB_SHIFT)

#define BG_SIZE_MASK	0xC000
#define BG_SIZE_SHIFT		14
#define BG_SIZE(n)		((n)<<BG_SIZE_SHIFT)

//== REG_KEYINPUT

#define KEY_A			0x0001	//!< Button A
#define KEY_B			0x0002	//!< Button B
#define KEY_SELECT	0x0004	//!< Select button
#define KEY_START		0x0008	//!< Start button
#define KEY_RIGHT		0x0010	//!< Right D-pad
#define KEY_LEFT		0x0020	//!< Left D-pad
#define KEY_UP			0x0040	//!< Up D-pad
#define KEY_DOWN		0x0080	//!< Down D-pad
#define KEY_R			0x0100	//!< Shoulder R
#define KEY_L			0x0200	//!< Shoulder L

#define KEY_ACCEPT	0x0009	//!< Accept buttons: A or start
#define KEY_CANCEL	0x0002	//!< Cancel button: B (well, it usually is)
#define KEY_RESET		0x030C	//!< St+Se+L+R

#define KEY_FIRE		0x0003	//!< Fire buttons: A or B
#define KEY_SPECIAL	0x000C	//!< Special buttons: Select or Start
#define KEY_DIR		0x00F0	//!< Directions: left, right, up down
#define KEY_SHOULDER	0x0300	//!< L or R

#define KEY_ANY		0x03FF	//!< Here's the Any key :)

#define KEY_MASK		0x03FF


//==== Input

INLINE int bit_tribool(u32 x, uint plus, uint minus);

INLINE int bit_tribool(u32 flags, uint plus, uint minus)
{	return ((flags>>plus)&1) - ((flags>>minus)&1);	}

// Constants
typedef enum eKeyIndex
{
	KI_A=0, KI_B, KI_SELECT, KI_START, 
	KI_RIGHT, KI_LEFT, KI_UP, KI_DOWN,
	KI_R, KI_L, KI_MAX
} eKeyIndex;

#define KEY_FULL	0xFFFFFFFF		//!< Define for checking all keys.

// Macros

// Check which of the specified keys are down or up right now

#define KEY_DOWN_NOW(key)	(~(REG_KEYINPUT) & key)
#define KEY_UP_NOW(key)		( (REG_KEYINPUT) & key)	

// test whether all keys are pressed, released, whatever.
// Example use:
//   KEY_EQ(key_hit, KEY_L | KEY_R)
// will be true if and only if KEY_L and KEY_R are _both_ being pressed
#define KEY_EQ(key_fun, keys)	( key_fun(keys) == (keys) )

#define KEY_TRIBOOL(fnKey, plus, minus)	\
	( bit_tribool(fnKey(KEY_FULL), plus, minus) )

// Globals
extern u16 __key_curr, __key_prev;

// Prototypes
void key_wait_for_clear(u32 key);

// Synchronous keystates
void key_poll();
INLINE u32 key_curr_state(void);
INLINE u32 key_prev_state(void);

INLINE u32 key_is_down(u32 key);
INLINE u32 key_is_up(u32 key);

INLINE u32 key_was_down(u32 key);
INLINE u32 key_was_up(u32 key);

// Transitional keystates
INLINE u32 key_transit(u32 key);
INLINE u32 key_held(u32 key);
INLINE u32 key_hit(u32 key);
INLINE u32 key_released(u32 key);

// Tribools
INLINE int key_tri_horz(void);
INLINE int key_tri_vert(void);
INLINE int key_tri_shoulder(void);
INLINE int key_tri_fire(void);

// Key repeats
u32 key_repeat(u32 keys);

void key_repeat_mask(u32 mask);
void key_repeat_limits(u32 delay, u32 repeat);

void key_wait_till_hit(u16 key);

//== Inlines

//! Get current keystate
INLINE u32 key_curr_state(void)		{	return __key_curr;			}

//! Get previous key state
INLINE u32 key_prev_state(void)		{	return __key_prev;			}

//! Gives the keys of \a key that are currently down
INLINE u32 key_is_down(u32 key)		{	return  __key_curr & key;	}

//! Gives the keys of \a key that are currently up
INLINE u32 key_is_up(u32 key)		{	return ~__key_curr & key;	}

//! Gives the keys of \a key that were previously down
INLINE u32 key_was_down(u32 key)	{	return  __key_prev & key;	}

//! Gives the keys of \a key that were previously down
INLINE u32 key_was_up(u32 key)		{	return ~__key_prev & key;	}



//! Gives the keys of \a key that are different from before
INLINE u32 key_transit(u32 key)
{	return ( __key_curr ^  __key_prev) & key;	}

//! Gives the keys of \a key that are being held down
INLINE u32 key_held(u32 key)
{	return ( __key_curr &  __key_prev) & key;	}

//! Gives the keys of \a key that are pressed (down now but not before)
INLINE u32 key_hit(u32 key)
{	return ( __key_curr &~ __key_prev) & key;	}

//! Gives the keys of \a key that are being released
INLINE u32 key_released(u32 key)
{	return (~__key_curr &  __key_prev) & key;	}



//! Horizontal tribool (right,left)=(+,-)
INLINE int key_tri_horz(void)		
{	return bit_tribool(__key_curr, KI_RIGHT, KI_LEFT);	}

//! Vertical tribool (down,up)=(+,-)
INLINE int key_tri_vert(void)		
{	return bit_tribool(__key_curr, KI_DOWN, KI_UP);		}

//! Shoulder-button tribool (R,L)=(+,-)
INLINE int key_tri_shoulder(void)	
{	return bit_tribool(__key_curr, KI_R, KI_L);			}

//! Fire-button tribool (A,B)=(+,-)
INLINE int key_tri_fire(void)		
{	return bit_tribool(__key_curr, KI_A, KI_B);			}



//==== Functions

//== Inlines

INLINE u16 RGB15(u32 red, u32 green, u32 blue)
{		return red | (green<<5) | (blue<<10);		}

//== Prototypes

void vid_vsync();

void setPixel(int,int,u16);

void drawRect(int,int,int,int,u16);

void drawHollowRect(int,int,int,int,u16);



#endif // MYLIB_H




