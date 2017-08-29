#include "platform.h"

unsigned long colors[] = {
	0x000000,
	0x0000ff,
	0x00ff00,
	0x00ffff,
	0xff0000,
	0xff00ff,
	0xffff00,
	0xffffff,

	0xf00000,
	0x00f07f,
	0x007ff0,
	0xf07f7f,
	0x7f00f0,
	0x7ff07f,
	0x7f7ff0,
	0x7f7f7f,
};

int
main(void)
{
	unsigned int i, j;
	platform_init();

	for(i = 0; i < 16; i++)
		for(j = 1; j <= 16; j++)
			setcolor(i*16 + j, (colors[i] & 0xff) / j | ((((colors[i] >> 8) & 0xff) / j ) << 8) | ((((colors[i] >> 16) & 0xff) / j) << 16));

	/* setcolor(1, 0xf92672); */

	for(i = 0; i < 640; i++)
		for(j = 0; j < 400; j++)
			drawpixel(i, j, i % 256);

	return 0;
}
