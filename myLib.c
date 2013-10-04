#include "myLib.h"

unsigned short * videoBuffer = (unsigned short *)0x6000000;

void setPixel(int row, int col, unsigned short color)
{
	videoBuffer[OFFSET(row,col, 240)] = color;
}

void drawRect(int row, int col, int width, int height, unsigned short color)
{
	int r;
	int c;
	for(r = 0; r <= height; r++){
		for(c = 0; c <= width; c++){
			setPixel(row+r, col+c, color);
		}
	}
}

void waitForVBlank()
{
	while(SCANLINECOUNTER>160);
	while(SCANLINECOUNTER<160);
}


void delay(int x){
     int i;
     int count;
     for(i=0;i<x;i++){
         count++;
     } 
}

extern u16 __key_curr, __key_prev;
u16 __key_curr=0, __key_prev=0;

inline void key_poll() {
    __key_prev= __key_curr;
    __key_curr= ~BUTTON_ADDRESS & KEY_MASK;
}

inline u32 key_curr_state() {return __key_curr;}
inline u32 key_prev_state()  {  return __key_prev;}
inline u32 key_is_down(u32 key) { return __key_curr & key;  }
inline u32 key_is_up(u32 key) {return ~__key_curr & key; }
inline u32 key_was_down(u32 key) { return __key_prev & key; }
inline u32 key_was_up(u32 key)  {   return ~__key_prev & key; } 
inline u32 key_held(u32 key){ return ( __key_curr & __key_prev) & key; }
inline u32 key_hit(u32 key){ return ( __key_curr &~ __key_prev) & key; }
inline u32 key_released(u32 key) { return (~__key_curr & __key_prev) & key; }
