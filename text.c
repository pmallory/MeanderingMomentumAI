#include "text.h"
#include "myLib.h"

void drawString(int row, int col, char *str, unsigned short color)
{
    while(*str)
    {
        drawChar(row, col, *str++, color);
        col += 6;
    }
}

void drawChar(int row, int col, char ch, unsigned short color)
{
    int r,c;
    for(r=0; r<8; r++)
    {
        for(c=0; c<6; c++)
        {
            if(fontdata_6x8[OFFSET(r, c, 6) + 48*ch])
            {
                setPixel(row+r, col+c, color);
            }
        }
    }
}

