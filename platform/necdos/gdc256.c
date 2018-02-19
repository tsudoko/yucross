#include <stdio.h>
#include <machine.h> /* FIXME */

/*
 * Non-standard syntax: far pointers; the "far" qualifier needs to be at the end
 * because some compilers crap out otherwise
 *
 * Assumptions:
 *  - 640x400
 *  - 8 colors
 *  - 256c packed pixel mode
 */

unsigned char far *PIXELS     = (unsigned char far *)0xa8000000;
unsigned int  far *MMIO_BANK1 = (unsigned int far *) 0xe0000004;
const int pscreenw = 640; /* XXX */
const int pscreenh = 400; /* XXX */
const int pcolors = 256;

void
pinit(void)
{
	outp8(0x6a, 0x07);
	outp8(0x6a, 0x21);

	outp8(0x62, 0x0c); /* stop text */
	outp8(0xa2, 0x0d); /* start graphics */
}

void
pdeinit(void)
{
	outp8(0xa2, 0x0c); /* stop graphics */
	outp8(0x62, 0x0d); /* start text */
}

void
psetcolor(unsigned char index, unsigned long color)
{
	outp8(0xa8, index);
	outp8(0xac, (color >> 16) & 0xff);
	outp8(0xaa, (color >> 8)  & 0xff);
	outp8(0xae,  color        & 0xff);
}

void
pdrawpixel(int x, int y, unsigned char color)
{
	unsigned long pos = 640L * y + x;
	*MMIO_BANK1 = (unsigned int)(pos >> 15);
	PIXELS[pos & 32767] = color;
}
