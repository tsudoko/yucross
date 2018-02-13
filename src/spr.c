#include <assert.h>

#include "stuff.h"

int
loadspr(char *path, Sprite *s)
{
	char buf[16];
	int x, y;
	int bufl = 0;
	FILE *f = fopen(path, "rb");

	if(fread(buf, 1, strlen("sprite "), f) != 7)
		return -1;

	if(memcmp(buf, "sprite ", strlen("sprite ")) != 0) /* bad magic */
		return -1;

	fscanf(f, "%d %d ", &(s->w), &(s->h));
	assert(s->w && s->h);
	printf("%s: %dx%d\n", path, s->w, s->h);
	s->data = malloc(s->w*s->h);

	do {
		buf[0] = fgetc(f);
	} while(buf[0] != '\n');

	printf("past the header\n");

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
					printf("pixel (%d, %d) '%c'\n", x, y, buf[bufl]);
					bufl++;
				}
			} while(!bufl && buf[bufl]);
			printf("process'd: %d\n", atoi(buf));
			
			s->data[y*s->w + x] = atoi(buf);
		}
	}

	return 0;
}
