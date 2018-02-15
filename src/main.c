#include <assert.h>
#include <time.h>

#include "../platform.h"

#include "stuff.h"

int mx, my;
char mbut;
char running;

void
drawhintrow(Stage *stage, Sprite *tiles, int *hints, int n, int y)
{
	int i, x1;
	x1 = stage->x - tiles->h - n*tiles->h;
	assert(x1 >= 0);

	for(i = 0; i < n; i++) {
		drawtile(x1 + i*16, stage->y + y*16, tiles, SPR_GUIDE);
		drawtile(x1 + i*16, stage->y + y*16, tiles, SPR_NUMBER + hints[i]);
	}
}

void
drawhintcol(Stage *stage, Sprite *tiles, int *hints, int n, int x)
{
	int i, y1;
	y1 = stage->y - tiles->h - n*tiles->h;
	assert(y1 >= 0);

	for(i = 0; i < n; i++) {
		drawtile(stage->x + x*16, y1 + i*16, tiles, SPR_GUIDE);
		drawtile(stage->x + x*16, y1 + i*16, tiles, SPR_NUMBER + hints[i]);
	}
}

void
hintdraw(Stage *stage, Sprite *tiles)
{
	int ir = 0;
	int x, y;
	char cons = 0;
	int *row = malloc(sizeof (int) * stage->y);

	for(y = 0; y < stage->h; y++) {
		ir = 0;
		row[ir] = 0;
		cons = 0;
		for(x = 0; x < stage->w; x++) {
			if(stage->pattern[y*stage->w + x]) {
				row[ir]++;
				cons = 1;
			} else if(cons) {
				cons = 0;
				ir++;
				row[ir] = 0;
			}
		}
		drawhintrow(stage, tiles, row, ir+(row[ir] ? 1 : 0), y);
	}

	for(x = 0; x < stage->w; x++) {
		ir = 0;
		row[ir] = 0;
		cons = 0;
		for(y = 0; y < stage->h; y++) {
			if(stage->pattern[y*stage->w + x]) {
				row[ir]++;
				cons = 1;
			} else if(cons) {
				cons = 0;
				ir++;
				row[ir] = 0;
			}
		}
		drawhintcol(stage, tiles, row, ir+(row[ir] ? 1 : 0), x);
	}

	free(row);
}

void
stagedraw(Stage *stage, Sprite *tiles)
{

	int x, y;

	for(y = 0; y < stage->h; y++) {
		for(x = 0; x < stage->w; x++) {
			drawtile(stage->x+(x*tiles->h), stage->y+(y*tiles->h), tiles, stage->tiles[y*stage->w + x] ? 1 : 0);
		}
	}
}

void
stageclick(Stage *stage, int x, int y)
{
	int tilesize = 16; /* XXX */
	char *tile;

	if(x < stage->x || y < stage->y)
		return;

	x -= stage->x;
	y -= stage->y;

	x /= tilesize; /* XXX */
	y /= tilesize; /* XXX */

	if(x > stage->w || y > stage->h)
		return;

	tile = &stage->tiles[y*stage->w + x];
	*tile = *tile ? 0 : 1; /* XXX */
}

int
won(Stage *stage)
{
	int i;
	for(i = 0; i < stage->w*stage->h; i++)
		if(stage->tiles[i] != stage->pattern[i])
			return 0;

	return !0;
}

void
deinit(Stage *stage) {
	delstage(stage);
	platform_deinit();
	mousedeinit();
	running = 0;
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
		if(won(s)) {
			printf("stage clear\n");
			deinit(s);
		}
	}
}

int
main(void)
{
	Stage *stage;
	Sprite *tiles;
	int colors;
	int i;

	running = 1;
	platform_init();
	mouseinit();
	stage = newstage(12, 12);
	colors = loadpal("res/pink.pal");
	loadspr("res/tile.spr", tiles);

	srand(time(NULL));

	for(i = 0; i < stage->w*stage->h; i++)
		stage->pattern[i] = rand()%2;

	stage->x = platform_screenw/2 - (stage->w*tiles->h)/2;
	stage->y = platform_screenh/2 - (stage->h*tiles->h)/2;

	hintdraw(stage, tiles);
	stagedraw(stage, tiles);

	/* mousecallback(tick); */

	/* while(platform_event())? */
	while(running) {
		tick(stage);
		stagedraw(stage, tiles);
	}

	deinit(stage);
	return 0;
}
