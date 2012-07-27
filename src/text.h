#ifndef TEXT_H
#define TEXT_H

#include "mylib.h"

extern const unsigned char fontdata[1536];
#define TEXT_WIDTH 6
#define TEXT_HEIGHT 8


void print_ch(char l, int x, int y, u16 c);

void println(char* s, int x, int y, int h, int v, u16 c);

#endif
