#include "pikmin.h"
#include "collision.h"


void init_pikmin(u32 num)
{
   PIKMIN* p = pkm;
   
   while(num--)
   {
      p.hp = PKM_HP;
      p.atk = PKM_ATK;
      p.spd = PKM_SPD;
      p.update = update_pikmin;
      p.animate = animate_pikmin;
      p.action_callback = 0;
      
      p++;
   }
}

void update_pikmin(PIKMIN* pkm)
{
   if(pkm->state & DEAD)
      return;
   
   if(pkm->state & SEED)
   {
      
      return;
   }
   
   if(pkm->state & STANDBY)
   {
      
      return;
   }
   
   if(pkm->state & FOLLOW)
   {
   
   }
   
   if(pkm->state & MARCH)
   {
      
   }
   
   if(pkm->state & THROWN)
   {
   
   }
   
   if(pkm->state & ACTION)
   {
   
   }
}
