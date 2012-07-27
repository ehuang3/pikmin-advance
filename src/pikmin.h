#ifndef PIKMIN_H
#define PIKMIN_H

#include "mylib.h"
#include "character.h"


#define MAX_PIKMIN 10

typedef OBJ PIKMIN;

// Globals

PIKMIN* pkm;

//Constants
#define PKM_HP = 10;
#define PKM_SPD = 5;
#define PKM_ATK = 1;
          
// States     
#define DEAD      1
#define SEED      2
#define STANDBY   4
#define FOLLOW    8
#define MARCH     16
#define THROWN    32
#define ACTION    64

// Static functions

void init_pikmin(u32 num);

// Functions

void update(PIKMIN* pkm);

void animate(PIKMIN* pkm);

void whistle(PIKMIN* pkm);

void seed(PIKMIN* pkm);

#endif
