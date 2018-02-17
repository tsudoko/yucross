#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "../platform.h"
#include "stuff.h"

int
loadpal(char *path)
{
	char buf[16];
	unsigned int blen = 0,
	             curcol = 0,
	             colors = -1;
	long col = 0;
	FILE *f = fopen(path, "rb");
	if(f == NULL)
		return -1;

	if(fread(buf, 1, strlen("pal "), f) != 4)
		return -1;

	if(memcmp(buf, "pal ", strlen("pal ")) != 0) /* bad magic */
		return -1;

	do {
		assert(blen <= nelem(buf));
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
		if(curcol) /* color 0 is transparent */
			setcolor(curcol, col);
		curcol++;
	} while(curcol < colors);

	return colors;
}

int
loadspr(char *path, Sprite *s)
{
	char buf[16];
	int x, y;
	int bufl = 0;
	FILE *f = fopen(path, "rb");
	if(f == NULL)
		return -1;

	if(fread(buf, 1, strlen("sprite "), f) != 7)
		return -1;

	if(memcmp(buf, "sprite ", strlen("sprite ")) != 0) /* bad magic */
		return -1;

	fscanf(f, "%d %d ", &(s->w), &(s->h));
	assert(s->w && s->h);
	s->data = malloc(s->w*s->h);

	do {
		buf[0] = fgetc(f);
	} while(buf[0] != '\n');

	for(y = 0; y < s->h; y++) {
		for(x = 0; x < s->w; x++) {
			bufl = 0;
			do {
				buf[bufl] = fgetc(f);
				assert(buf[bufl] != 255);
				if(buf[bufl] == ' ' || buf[bufl] == '\n') {
					if(bufl)
						buf[bufl] = '\0';
				} else {
					bufl++;
				}
			} while(!bufl && buf[bufl]);

			s->data[y*s->w + x] = atoi(buf);
		}
	}

	return 0;
}
