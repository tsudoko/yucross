#include "platform.h"

#include "stage.h"
#include "stuff.h"

int
main(void)
{
	Stage *s;
	Sprite *tiles;
	int colors;
	int i, j;
	platform_init();
	s = newstage(12*12);
	colors = loadpal("res\\pink.pal");
	loadspr("res\\tile.spr", tiles);
	printf("tileset loaded\n");
	drawspr(50, 30, tiles);
	printf("tileset drawn\n");
	for(i = 0; i < colors; i++) {
		for(j = i*4; j < i*4+4; j++) {
			drawpixel(j, j, i);
			drawpixel(j, j+1, i);
			drawpixel(j, j+2, i);
			drawpixel(j, j+3, i);
		}
	}
	
	delstage(s);
	/* platform_deinit(); */
	return 0;
}
