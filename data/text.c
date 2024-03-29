#include "text.h"
#include <debugging.h>

void println(char* s, int x, int y, int h, int v, u16 c)
{
   int cx = x;
   int cy = y;
   
   while(*s != 0)
   {
      print_ch(*s, cx, cy, c);
      
      cx += h + 6;
      cy += v;
      
      s ++;
   }
}

void print_ch(char l, int x, int y, u16 c)
{
   u32 line = TEXT_WIDTH;
   while(line--)
   {
      u32 bits = fontdata[l*6+line];
      u32 row = TEXT_HEIGHT;
      while(row--)
      {
         if(bits & 1)
            setPixel(x+line, y+row, c);
         bits = bits >> 1;
      }
   }
}


/* represents all 256 ascii characters in a single character array */

const unsigned char fontdata[1536] = {
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* num: 0 */
0x00, 0x7c, 0xa2, 0x8a, 0xa2, 0x7c, /* num: 1 */
0x00, 0x7c, 0xd6, 0xf6, 0xd6, 0x7c, /* num: 2 */
0x00, 0x38, 0x7c, 0x3e, 0x7c, 0x38, /* num: 3 */
0x00, 0x00, 0x38, 0x1c, 0x38, 0x00, /* num: 4 */
0x00, 0x0c, 0x6c, 0xfe, 0x6c, 0x0c, /* num: 5 */
0x00, 0x18, 0x3a, 0x7e, 0x3a, 0x18, /* num: 6 */
0x00, 0x00, 0x18, 0x18, 0x00, 0x00, /* num: 7 */
0xff, 0xff, 0xe7, 0xe7, 0xff, 0xff, /* num: 8 */
0x00, 0x3c, 0x24, 0x24, 0x3c, 0x00, /* num: 9 */
0xff, 0xc3, 0xdb, 0xdb, 0xc3, 0xff, /* num: 10 */
0x00, 0x0c, 0x12, 0x52, 0x6c, 0x70, /* num: 11 */
0x00, 0x60, 0x94, 0x9e, 0x94, 0x60, /* num: 12 */
0x00, 0x06, 0x0e, 0xfc, 0x40, 0x20, /* num: 13 */
0x00, 0x06, 0x7e, 0x50, 0xac, 0xfc, /* num: 14 */
0x00, 0x54, 0x38, 0x6c, 0x38, 0x54, /* num: 15 */
0x00, 0x00, 0xfe, 0x7c, 0x38, 0x10, /* num: 16 */
0x00, 0x10, 0x38, 0x7c, 0xfe, 0x00, /* num: 17 */
0x00, 0x28, 0x6c, 0xfe, 0x6c, 0x28, /* num: 18 */
0x00, 0x00, 0xfa, 0x00, 0xfa, 0x00, /* num: 19 */
0x00, 0x60, 0x90, 0xfe, 0x80, 0xfe, /* num: 20 */
0x00, 0x44, 0xb2, 0xaa, 0x9a, 0x44, /* num: 21 */
0x00, 0x06, 0x06, 0x06, 0x06, 0x00, /* num: 22 */
0x00, 0x28, 0x6d, 0xff, 0x6d, 0x28, /* num: 23 */
0x00, 0x20, 0x60, 0xfe, 0x60, 0x20, /* num: 24 */
0x00, 0x08, 0x0c, 0xfe, 0x0c, 0x08, /* num: 25 */
0x00, 0x10, 0x10, 0x7c, 0x38, 0x10, /* num: 26 */
0x00, 0x10, 0x38, 0x7c, 0x10, 0x10, /* num: 27 */
0x00, 0x1e, 0x02, 0x02, 0x02, 0x02, /* num: 28 */
0x00, 0x10, 0x7c, 0x10, 0x7c, 0x10, /* num: 29 */
0x00, 0x0c, 0x3c, 0xfc, 0x3c, 0x0c, /* num: 30 */
0x00, 0xc0, 0xf0, 0xfc, 0xf0, 0xc0, /* num: 31 */
0x00, 0x00, 0x00, 0x00, 0x00, 0x00, /* num: 32 */
0x00, 0x00, 0x60, 0xfa, 0x60, 0x00, /* num: 33 */
0x00, 0xe0, 0xc0, 0x00, 0xe0, 0xc0, /* num: 34 */
0x00, 0x24, 0x7e, 0x24, 0x7e, 0x24, /* num: 35 */
0x00, 0x24, 0xd4, 0x56, 0x48, 0x00, /* num: 36 */
0x00, 0xc6, 0xc8, 0x10, 0x26, 0xc6, /* num: 37 */
0x00, 0x6c, 0x92, 0x6a, 0x04, 0x0a, /* num: 38 */
0x00, 0x00, 0xe0, 0xc0, 0x00, 0x00, /* num: 39 */
0x00, 0x00, 0x7c, 0x82, 0x00, 0x00, /* num: 40 */
0x00, 0x00, 0x82, 0x7c, 0x00, 0x00, /* num: 41 */
0x00, 0x10, 0x7c, 0x38, 0x7c, 0x10, /* num: 42 */
0x00, 0x10, 0x10, 0x7c, 0x10, 0x10, /* num: 43 */
0x00, 0x00, 0x07, 0x06, 0x00, 0x00, /* num: 44 */
0x00, 0x10, 0x10, 0x10, 0x10, 0x10, /* num: 45 */
0x00, 0x00, 0x06, 0x06, 0x00, 0x00, /* num: 46 */
0x00, 0x04, 0x08, 0x10, 0x20, 0x40, /* num: 47 */
0x00, 0x7c, 0x8a, 0x92, 0xa2, 0x7c, /* num: 48 */
0x00, 0x00, 0x42, 0xfe, 0x02, 0x00, /* num: 49 */
0x00, 0x46, 0x8a, 0x92, 0x92, 0x62, /* num: 50 */
0x00, 0x44, 0x92, 0x92, 0x92, 0x6c, /* num: 51 */
0x00, 0x18, 0x28, 0x48, 0xfe, 0x08, /* num: 52 */
0x00, 0xf4, 0x92, 0x92, 0x92, 0x8c, /* num: 53 */
0x00, 0x3c, 0x52, 0x92, 0x92, 0x0c, /* num: 54 */
0x00, 0x80, 0x8e, 0x90, 0xa0, 0xc0, /* num: 55 */
0x00, 0x6c, 0x92, 0x92, 0x92, 0x6c, /* num: 56 */
0x00, 0x60, 0x92, 0x92, 0x94, 0x78, /* num: 57 */
0x00, 0x00, 0x36, 0x36, 0x00, 0x00, /* num: 58 */
0x00, 0x00, 0x37, 0x36, 0x00, 0x00, /* num: 59 */
0x00, 0x10, 0x28, 0x44, 0x82, 0x00, /* num: 60 */
0x00, 0x24, 0x24, 0x24, 0x24, 0x24, /* num: 61 */
0x00, 0x00, 0x82, 0x44, 0x28, 0x10, /* num: 62 */
0x00, 0x40, 0x80, 0x9a, 0x90, 0x60, /* num: 63 */
0x00, 0x7c, 0x82, 0xba, 0xaa, 0x78, /* num: 64 */
0x00, 0x7e, 0x88, 0x88, 0x88, 0x7e, /* num: 65 */
0x00, 0xfe, 0x92, 0x92, 0x92, 0x6c, /* num: 66 */
0x00, 0x7c, 0x82, 0x82, 0x82, 0x44, /* num: 67 */
0x00, 0xfe, 0x82, 0x82, 0x82, 0x7c, /* num: 68 */
0x00, 0xfe, 0x92, 0x92, 0x92, 0x82, /* num: 69 */
0x00, 0xfe, 0x90, 0x90, 0x90, 0x80, /* num: 70 */
0x00, 0x7c, 0x82, 0x92, 0x92, 0x5e, /* num: 71 */
0x00, 0xfe, 0x10, 0x10, 0x10, 0xfe, /* num: 72 */
0x00, 0x00, 0x82, 0xfe, 0x82, 0x00, /* num: 73 */
0x00, 0x0c, 0x02, 0x02, 0x02, 0xfc, /* num: 74 */
0x00, 0xfe, 0x10, 0x28, 0x44, 0x82, /* num: 75 */
0x00, 0xfe, 0x02, 0x02, 0x02, 0x02, /* num: 76 */
0x00, 0xfe, 0x40, 0x20, 0x40, 0xfe, /* num: 77 */
0x00, 0xfe, 0x40, 0x20, 0x10, 0xfe, /* num: 78 */
0x00, 0x7c, 0x82, 0x82, 0x82, 0x7c, /* num: 79 */
0x00, 0xfe, 0x90, 0x90, 0x90, 0x60, /* num: 80 */
0x00, 0x7c, 0x82, 0x8a, 0x84, 0x7a, /* num: 81 */
0x00, 0xfe, 0x90, 0x90, 0x98, 0x66, /* num: 82 */
0x00, 0x64, 0x92, 0x92, 0x92, 0x4c, /* num: 83 */
0x00, 0x80, 0x80, 0xfe, 0x80, 0x80, /* num: 84 */
0x00, 0xfc, 0x02, 0x02, 0x02, 0xfc, /* num: 85 */
0x00, 0xf8, 0x04, 0x02, 0x04, 0xf8, /* num: 86 */
0x00, 0xfc, 0x02, 0x3c, 0x02, 0xfc, /* num: 87 */
0x00, 0xc6, 0x28, 0x10, 0x28, 0xc6, /* num: 88 */
0x00, 0xe0, 0x10, 0x0e, 0x10, 0xe0, /* num: 89 */
0x00, 0x8e, 0x92, 0xa2, 0xc2, 0x00, /* num: 90 */
0x00, 0x00, 0xfe, 0x82, 0x82, 0x00, /* num: 91 */
0x00, 0x40, 0x20, 0x10, 0x08, 0x04, /* num: 92 */
0x00, 0x00, 0x82, 0x82, 0xfe, 0x00, /* num: 93 */
0x00, 0x20, 0x40, 0x80, 0x40, 0x20, /* num: 94 */
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, /* num: 95 */
0x00, 0x00, 0xc0, 0xe0, 0x00, 0x00, /* num: 96 */
0x00, 0x04, 0x2a, 0x2a, 0x2a, 0x1e, /* num: 97 */
0x00, 0xfe, 0x22, 0x22, 0x22, 0x1c, /* num: 98 */
0x00, 0x1c, 0x22, 0x22, 0x22, 0x14, /* num: 99 */
0x00, 0x1c, 0x22, 0x22, 0x22, 0xfe, /* num: 100 */
0x00, 0x1c, 0x2a, 0x2a, 0x2a, 0x10, /* num: 101 */
0x00, 0x10, 0x7e, 0x90, 0x90, 0x00, /* num: 102 */
0x00, 0x18, 0x25, 0x25, 0x25, 0x3e, /* num: 103 */
0x00, 0xfe, 0x20, 0x20, 0x1e, 0x00, /* num: 104 */
0x00, 0x00, 0x00, 0xbe, 0x02, 0x00, /* num: 105 */
0x00, 0x02, 0x01, 0x21, 0xbe, 0x00, /* num: 106 */
0x00, 0xfe, 0x08, 0x14, 0x22, 0x00, /* num: 107 */
0x00, 0x00, 0x00, 0xfe, 0x02, 0x00, /* num: 108 */
0x00, 0x3e, 0x20, 0x18, 0x20, 0x1e, /* num: 109 */
0x00, 0x3e, 0x20, 0x20, 0x1e, 0x00, /* num: 110 */
0x00, 0x1c, 0x22, 0x22, 0x22, 0x1c, /* num: 111 */
0x00, 0x3f, 0x22, 0x22, 0x22, 0x1c, /* num: 112 */
0x00, 0x1c, 0x22, 0x22, 0x22, 0x3f, /* num: 113 */
0x00, 0x22, 0x1e, 0x22, 0x20, 0x10, /* num: 114 */
0x00, 0x10, 0x2a, 0x2a, 0x2a, 0x04, /* num: 115 */
0x00, 0x20, 0x7c, 0x22, 0x24, 0x00, /* num: 116 */
0x00, 0x3c, 0x02, 0x04, 0x3e, 0x00, /* num: 117 */
0x00, 0x38, 0x04, 0x02, 0x04, 0x38, /* num: 118 */
0x00, 0x3c, 0x06, 0x0c, 0x06, 0x3c, /* num: 119 */
0x00, 0x36, 0x08, 0x08, 0x36, 0x00, /* num: 120 */
0x00, 0x39, 0x05, 0x06, 0x3c, 0x00, /* num: 121 */
0x00, 0x26, 0x2a, 0x2a, 0x32, 0x00, /* num: 122 */
0x00, 0x10, 0x7c, 0x82, 0x82, 0x00, /* num: 123 */
0x00, 0x00, 0x00, 0xff, 0x00, 0x00, /* num: 124 */
0x00, 0x00, 0x82, 0x82, 0x7c, 0x10, /* num: 125 */
0x00, 0x40, 0x80, 0x40, 0x80, 0x00, /* num: 126 */
0x00, 0x3c, 0x64, 0xc4, 0x64, 0x3c, /* num: 127 */
0x00, 0x78, 0x85, 0x87, 0x84, 0x48, /* num: 128 */
0x00, 0xbc, 0x02, 0x04, 0xbe, 0x00, /* num: 129 */
0x00, 0x1c, 0x2a, 0x2a, 0xaa, 0x90, /* num: 130 */
0x00, 0x04, 0xaa, 0xaa, 0xaa, 0x1e, /* num: 131 */
0x00, 0x04, 0xaa, 0x2a, 0xaa, 0x1e, /* num: 132 */
0x00, 0x04, 0xaa, 0xaa, 0x2a, 0x1e, /* num: 133 */
0x00, 0x04, 0xea, 0xaa, 0xea, 0x1e, /* num: 134 */
0x00, 0x38, 0x45, 0x47, 0x44, 0x28, /* num: 135 */
0x00, 0x1c, 0xaa, 0xaa, 0xaa, 0x10, /* num: 136 */
0x00, 0x1c, 0xaa, 0x2a, 0xaa, 0x10, /* num: 137 */
0x00, 0x1c, 0xaa, 0xaa, 0x2a, 0x10, /* num: 138 */
0x00, 0x00, 0x80, 0x3e, 0x82, 0x00, /* num: 139 */
0x00, 0x00, 0x40, 0x9e, 0x42, 0x00, /* num: 140 */
0x00, 0x00, 0x80, 0x3e, 0x02, 0x00, /* num: 141 */
0x00, 0x0e, 0x94, 0x24, 0x94, 0x0e, /* num: 142 */
0x00, 0x1e, 0xf4, 0xa4, 0xf4, 0x1e, /* num: 143 */
0x00, 0x3e, 0x2a, 0x2a, 0xaa, 0xa2, /* num: 144 */
0x00, 0x2c, 0x2a, 0x3e, 0x2a, 0x1a, /* num: 145 */
0x00, 0x7e, 0x90, 0xfe, 0x92, 0x92, /* num: 146 */
0x00, 0x1c, 0xa2, 0xa2, 0x9c, 0x00, /* num: 147 */
0x00, 0x1c, 0xa2, 0x22, 0x9c, 0x00, /* num: 148 */
0x00, 0x9c, 0xa2, 0x22, 0x1c, 0x00, /* num: 149 */
0x00, 0x3c, 0x82, 0x84, 0xbe, 0x00, /* num: 150 */
0x00, 0xbc, 0x82, 0x04, 0x3e, 0x00, /* num: 151 */
0x00, 0x39, 0x85, 0x06, 0xbc, 0x00, /* num: 152 */
0x00, 0xbc, 0x42, 0x42, 0xbc, 0x00, /* num: 153 */
0x00, 0x3c, 0x82, 0x02, 0xbc, 0x00, /* num: 154 */
0x00, 0x18, 0x24, 0x66, 0x24, 0x00, /* num: 155 */
0x00, 0x12, 0x7c, 0x92, 0x92, 0x46, /* num: 156 */
0x00, 0x94, 0x54, 0x3e, 0x54, 0x94, /* num: 157 */
0x00, 0xfe, 0x90, 0x68, 0x1e, 0x08, /* num: 158 */
0x00, 0x02, 0x11, 0x7e, 0x90, 0x40, /* num: 159 */
0x00, 0x04, 0x2a, 0xaa, 0xaa, 0x1e, /* num: 160 */
0x00, 0x00, 0x00, 0xbe, 0x82, 0x00, /* num: 161 */
0x00, 0x1c, 0x22, 0xa2, 0x9c, 0x00, /* num: 162 */
0x00, 0x3c, 0x02, 0x84, 0xbe, 0x00, /* num: 163 */
0x00, 0x5e, 0x90, 0x50, 0x8e, 0x00, /* num: 164 */
0x00, 0x5e, 0x88, 0x44, 0x9e, 0x00, /* num: 165 */
0x00, 0x10, 0xaa, 0xaa, 0xaa, 0x7a, /* num: 166 */
0x00, 0x72, 0x8a, 0x8a, 0x72, 0x00, /* num: 167 */
0x00, 0x0c, 0x12, 0xb2, 0x02, 0x04, /* num: 168 */
0x00, 0x3c, 0x20, 0x20, 0x20, 0x20, /* num: 169 */
0x20, 0x20, 0x20, 0x20, 0x20, 0x38, /* num: 170 */
0x00, 0xe8, 0x10, 0x32, 0x56, 0x0a, /* num: 171 */
0x00, 0xe8, 0x10, 0x2c, 0x54, 0x1e, /* num: 172 */
0x00, 0x00, 0x0c, 0xbe, 0x0c, 0x00, /* num: 173 */
0x00, 0x10, 0x28, 0x00, 0x10, 0x28, /* num: 174 */
0x00, 0x28, 0x10, 0x00, 0x28, 0x10, /* num: 175 */
0x22, 0x88, 0x22, 0x88, 0x22, 0x88, /* num: 176 */
0x55, 0xaa, 0x55, 0xaa, 0x55, 0xaa, /* num: 177 */
0xdd, 0x77, 0xdd, 0x77, 0xdd, 0x77, /* num: 178 */
0x00, 0x00, 0x00, 0xff, 0x00, 0x00, /* num: 179 */
0x10, 0x10, 0x10, 0xff, 0x00, 0x00, /* num: 180 */
0x00, 0x3f, 0x04, 0x04, 0x38, 0x00, /* num: 181 */
0x10, 0xff, 0x00, 0xff, 0x00, 0x00, /* num: 182 */
0x10, 0x1f, 0x10, 0x1f, 0x00, 0x00, /* num: 183 */
0x50, 0x50, 0x50, 0x7f, 0x00, 0x00, /* num: 184 */
0x50, 0xdf, 0x00, 0xff, 0x00, 0x00, /* num: 185 */
0x00, 0xff, 0x00, 0xff, 0x00, 0x00, /* num: 186 */
0x50, 0x5f, 0x40, 0x7f, 0x00, 0x00, /* num: 187 */
0x50, 0xd0, 0x10, 0xf0, 0x00, 0x00, /* num: 188 */
0x10, 0xf0, 0x10, 0xf0, 0x00, 0x00, /* num: 189 */
0x50, 0x50, 0x50, 0xf0, 0x00, 0x00, /* num: 190 */
0x10, 0x10, 0x10, 0x1f, 0x00, 0x00, /* num: 191 */
0x00, 0x00, 0x00, 0xf0, 0x10, 0x10, /* num: 192 */
0x10, 0x10, 0x10, 0xf0, 0x10, 0x10, /* num: 193 */
0x10, 0x10, 0x10, 0x1f, 0x10, 0x10, /* num: 194 */
0x00, 0x00, 0x00, 0xff, 0x10, 0x10, /* num: 195 */
0x10, 0x10, 0x10, 0x10, 0x10, 0x10, /* num: 196 */
0x10, 0x10, 0x10, 0xff, 0x10, 0x10, /* num: 197 */
0x00, 0x00, 0x00, 0xff, 0x50, 0x50, /* num: 198 */
0x00, 0xff, 0x00, 0xff, 0x10, 0x10, /* num: 199 */
0x00, 0xf0, 0x10, 0xd0, 0x50, 0x50, /* num: 200 */
0x00, 0x7f, 0x40, 0x5f, 0x50, 0x50, /* num: 201 */
0x50, 0xd0, 0x10, 0xd0, 0x50, 0x50, /* num: 202 */
0x50, 0x5f, 0x40, 0x5f, 0x50, 0x50, /* num: 203 */
0x00, 0xff, 0x00, 0xdf, 0x50, 0x50, /* num: 204 */
0x50, 0x50, 0x50, 0x50, 0x50, 0x50, /* num: 205 */
0x50, 0xdf, 0x00, 0xdf, 0x50, 0x50, /* num: 206 */
0x50, 0x50, 0x50, 0xd0, 0x50, 0x50, /* num: 207 */
0x10, 0xf0, 0x10, 0xf0, 0x10, 0x10, /* num: 208 */
0x50, 0x50, 0x50, 0x5f, 0x50, 0x50, /* num: 209 */
0x10, 0x1f, 0x10, 0x1f, 0x10, 0x10, /* num: 210 */
0x00, 0xf0, 0x10, 0xf0, 0x10, 0x10, /* num: 211 */
0x01, 0x01, 0x01, 0x01, 0x01, 0x01, /* num: 212 */
0x03, 0x03, 0x03, 0x03, 0x03, 0x03, /* num: 213 */
0x07, 0x07, 0x07, 0x07, 0x07, 0x07, /* num: 214 */
0x0f, 0x0f, 0x0f, 0x0f, 0x0f, 0x0f, /* num: 215 */
0x1f, 0x1f, 0x1f, 0x1f, 0x1f, 0x1f, /* num: 216 */
0x3f, 0x3f, 0x3f, 0x3f, 0x3f, 0x3f, /* num: 217 */
0x7f, 0x7f, 0x7f, 0x7f, 0x7f, 0x7f, /* num: 218 */
0xff, 0xff, 0xff, 0xff, 0xff, 0xff, /* num: 219 */
0xff, 0x00, 0x00, 0x00, 0x00, 0x00, /* num: 220 */
0xff, 0xff, 0x00, 0x00, 0x00, 0x00, /* num: 221 */
0xff, 0xff, 0xff, 0x00, 0x00, 0x00, /* num: 222 */
0xff, 0xff, 0xff, 0xff, 0x00, 0x00, /* num: 223 */
0xff, 0xff, 0xff, 0xff, 0xff, 0x00, /* num: 224 */
0x00, 0x7f, 0x52, 0x52, 0x2c, 0x00, /* num: 225 */
0x00, 0xfe, 0x80, 0x80, 0xc0, 0x00, /* num: 226 */
0x00, 0x40, 0x7e, 0x40, 0x7e, 0x40, /* num: 227 */
0x00, 0x04, 0xaa, 0x2a, 0xaa, 0x1e, /* num: 228 */
0x00, 0x18, 0x24, 0x24, 0x38, 0x20, /* num: 229 */
0x00, 0x3f, 0x04, 0x04, 0x38, 0x00, /* num: 230 */
0x00, 0x10, 0x20, 0x1e, 0x20, 0x00, /* num: 231 */
0x00, 0x10, 0xaa, 0xee, 0xaa, 0x10, /* num: 232 */
0x00, 0x7c, 0x92, 0x92, 0x7c, 0x00, /* num: 233 */
0x00, 0x32, 0x4e, 0x40, 0x4e, 0x32, /* num: 234 */
0x00, 0x44, 0xaa, 0x9a, 0x0c, 0x00, /* num: 235 */
0x00, 0x18, 0x24, 0x18, 0x24, 0x18, /* num: 236 */
0x00, 0x18, 0x24, 0x7e, 0x24, 0x18, /* num: 237 */
0x00, 0x38, 0x54, 0x54, 0x54, 0x00, /* num: 238 */
0x00, 0x3c, 0x40, 0x40, 0x3c, 0x00, /* num: 239 */
0x00, 0x54, 0x54, 0x54, 0x54, 0x00, /* num: 240 */
0x00, 0x00, 0x24, 0x74, 0x24, 0x00, /* num: 241 */
0x00, 0x8a, 0x52, 0x52, 0x22, 0x00, /* num: 242 */
0x3f, 0x31, 0x31, 0x29, 0x29, 0x25, /* num: 243 */
0x25, 0x29, 0x29, 0x31, 0x31, 0x3f, /* num: 244 */
0x00, 0x04, 0x02, 0xfc, 0x00, 0x00, /* num: 245 */
0x00, 0x1c, 0xa2, 0x22, 0xa2, 0x1c, /* num: 246 */
0xff, 0xff, 0xff, 0xff, 0xff, 0x00, /* num: 247 */
0xff, 0xff, 0xff, 0xff, 0x00, 0x00, /* num: 248 */
0xff, 0xff, 0xff, 0x00, 0x00, 0x00, /* num: 249 */
0xff, 0xff, 0x00, 0x00, 0x00, 0x00, /* num: 250 */
0xff, 0x00, 0x00, 0x00, 0x00, 0x00, /* num: 251 */
0x00, 0x3c, 0x82, 0x04, 0xbe, 0x00, /* num: 252 */
0x00, 0x90, 0xb0, 0x50, 0x00, 0x00, /* num: 253 */
0x0e, 0x1e, 0x13, 0x13, 0x1f, 0x05, /* num: 254 */
0x48, 0xfc, 0x48, 0x48, 0xfc, 0x48  /* num: 255 */
};
