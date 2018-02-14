#include <machine.h>

#include "platform.h"

#include "stuff.h"

int mx, my;
char mbut;

#define screenw 640
#define screenh 400

int
stagedraw(Stage *stage, Sprite *tiles)
{

	int x1, y1;
	int x, y;

	x1 = screenw/2 - (stage->w*tiles->h)/2;
	y1 = screenh/2 - (stage->h*tiles->h)/2;

	for(y = 0; y < stage->h; y++) {
		for(x = 0; x < stage->w; x++) {
			drawtile(x1+(x*tiles->h), y1+(y*tiles->h), tiles, stage->tiles[y*stage->w + x] ? 1 : 0);
		}
	}
}

int
stageclick(Stage *stage, int x, int y)
{
	int tilesize = 16; /* XXX */
	char *tile;
	int x1, y1;

	/* TODO: keep stage position in Stage? */
	x1 = screenw/2 - (stage->w*tilesize)/2;
	y1 = screenh/2 - (stage->h*tilesize)/2;

	if(x < x1 || y < y1)
		return;

	x -= x1;
	y -= y1;

	x /= tilesize; /* XXX */
	y /= tilesize; /* XXX */

	if(x > stage->w || y > stage->h)
		return;

	tile = &stage->tiles[y*stage->w + x];
	*tile = *tile ? 0 : 1;
}

void
tick(Stage *s)
{

	/* TODO: don't poll when there's a callback set?
         *       not sure if we want to have that global state anyway though
         */
	mousestat(&mx, &my, &mbut);

	if(mbut) {
		printf("mouse click %d (%d, %d)\n", mbut, mx, my);
		stageclick(s, mx, my);
	}
}

int
main(void)
{
	Stage *stage;
	Sprite *tiles;
	int colors;
	platform_init();
	mouseinit();
	stage = newstage(12, 12);
	colors = loadpal("res\\pink.pal");
	loadspr("res\\tile.spr", tiles);

	drawtile(120, 71, tiles, 2);
	drawtile(125, 71, tiles, 2);
	drawtile(127, 71, tiles, 2);
	drawtile(128, 71, tiles, 2);

	stagedraw(stage, tiles);

	/* mousecallback(tick); */

	/* while(platform_event())? */
	for(;;) {
		tick(stage);
		stagedraw(stage, tiles);
	}

	delstage(stage);
	/* platform_deinit(); */
	mousedeinit();
	return 0;
}
