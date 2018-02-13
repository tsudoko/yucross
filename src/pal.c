/* #include "stuff.h" */
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "platform.h"

int
loadpal(char *path)
{
	char buf[16];
	unsigned int blen = 0,
	             curcol = 0,
	             colors = -1;
	long col = 0;
	FILE *f = fopen(path, "rb");

	if(fread(buf, 1, 4, f) != 4)
		return -1;

	if(memcmp(buf, "pal ", 4) != 0) /* bad magic */
		return -1;

	do {
		assert(blen <= (sizeof (buf) / sizeof *buf));
		buf[blen] = fgetc(f);
	} while(buf[blen++] != '\n');
	buf[blen] = '\0';
	colors = atoi(buf);
	blen = 0;

	do {
		while(blen < 8) {
			buf[blen] = fgetc(f);
			if(buf[blen] != '\n')
				blen++;
		}
		buf[blen++] = '\0';
		col = strtol(buf, NULL, 16);
		blen = 0;
		/* fscanf(f, "0x%06x\n", &col);
		fscanf(f, "%i\n", &col); */
		printf("doing color %x\n", col);
		if(curcol) /* color 0 is transparent */
			setcolor(curcol, col);
		/* assert(col != -1); */
		printf("ftell %d\n", ftell(f));
		curcol++;
	} while(curcol < colors);

	return colors;
}
