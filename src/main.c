#include "platform.h"

int
main(void)
{
	unsigned int i;
	platform_init();

	for(i = 1; i < 256; i++)
		setcolor(i, (unsigned long)((unsigned long)i*65793L));

	setcolor(1, 0xf92672);

	for(i = 0; i < 640; i++)
		drawpixel(i, i/2, 1);

	return 0;
}
