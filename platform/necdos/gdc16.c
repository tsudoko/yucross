#include <stdio.h>
#include <dos.h>

unsigned char far *PLANE0 = (unsigned char far *)MK_FP(0xa800, 0);
unsigned char far *PLANE1 = (unsigned char far *)MK_FP(0xb000, 0);
unsigned char far *PLANE2 = (unsigned char far *)MK_FP(0xb800, 0);
unsigned char far *PLANE3 = (unsigned char far *)MK_FP(0xe000, 0);
const int platform_colors = 16;

void
platform_init(void)
{
	outp8(0x6a, 0x01); /* 16 color mode */
	outp8(0x68, 1<<3|0); /* mode F/F bit 3 - column width (80 columns) */
	/* outp8(0xa2, 0x4b); /* 400 line mode */

	/*outp8(0x62, 0x0c); /* stop text */
	outp8(0xa2, 0x0d); /* start graphics */
}

void
setcolor(unsigned char index, unsigned long color)
{
	outp8(0xa8, index);
	outp8(0xac, ((color >> 16) & 0xff) >> 4);
	outp8(0xaa, ((color >> 8)  & 0xff) >> 4);
	outp8(0xae, ( color        & 0xff) >> 4);
}

void
drawpixel(int x, int y, unsigned char color)
{
	unsigned long pos = 640L * y + x;

	if(color & 1<<0)
		PLANE0[pos/8] |= 128>>(pos%8);
	else
		PLANE0[pos/8] &= ~(128>>(pos%8));
	if(color & 1<<1)
		PLANE1[pos/8] |= 128>>(pos%8);
	else
		PLANE1[pos/8] &= ~(128>>(pos%8));
	if(color & 1<<2)
		PLANE2[pos/8] |= 128>>(pos%8);
	else
		PLANE2[pos/8] &= ~(128>>(pos%8));
	if(color & 1<<3)
		PLANE3[pos/8] |= 128>>(pos%8);
	else
		PLANE3[pos/8] &= ~(128>>(pos%8));
}
