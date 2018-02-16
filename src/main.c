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
	int x, y;
	int ir;
	char cons;
	int row[16];

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
				assert(nelem(row) > ir);
				ir++;
				row[ir] = 0;
			}
		}
		if(row[ir])
			ir++;
		drawhintrow(stage, tiles, row, ir, y);
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
				assert(nelem(row) > ir);
				ir++;
				row[ir] = 0;
			}
		}
		if(row[ir])
			ir++;
		drawhintcol(stage, tiles, row, ir, x);
	}
}

void
drawstagetile(Stage *stage, Sprite *tiles, int x, int y)
{
	drawtile(stage->x+(x*tiles->h), stage->y+(y*tiles->h), tiles, stage->tiles[y*stage->w + x] ? 1 : 0);
}

void
stagedraw(Stage *stage, Sprite *tiles)
{

	int x, y;

	for(y = 0; y < stage->h; y++) {
		for(x = 0; x < stage->w; x++) {
			drawstagetile(stage, tiles, x, y);
		}
	}
}

void
stageclick(Stage *stage, Sprite *tiles, int x, int y)
{
	char *tile;

	if(x < stage->x || y < stage->y)
		return;

	x -= stage->x;
	y -= stage->y;

	x /= tiles->h;
	y /= tiles->h;

	if(x >= stage->w || y >= stage->h)
		return;

	tile = &stage->tiles[y*stage->w + x];
	*tile = *tile ? 0 : 1; /* XXX */
	drawstagetile(stage, tiles, x, y);
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
	/* TODO: free sprites (tiles, bg) */
	platform_deinit();
	hidecursor();
	running = 0;
}

void
tick(Stage *s, Sprite *tiles)
{

	/* TODO: don't poll when there's a callback set?
         *       not sure if we want to have that global state anyway though
         */
	mousestat(&mx, &my, &mbut);

	if(mbut) {
		if(mbut & 4) /* debug exit */
			deinit(s);
		/* printf("mouse click %d (%d, %d)\n", mbut, mx, my); */
		stageclick(s, tiles, mx, my);
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
	Sprite *tiles = malloc(sizeof *tiles);
	Sprite *bg = malloc(sizeof *bg);
	int colors;
	int i;

	running = 1;
	platform_init();
	if(mouseinit() < 0) {
		fprintf(stderr, "mouse initialization failed\n");
		platform_deinit();
		return -1;
	}

	stage = newstage(12, 12);
	colors = loadpal("res/pink.pal");
	if(colors < 0) {
		fprintf(stderr, "failed to load palette file\n");
		deinit(stage);
		return -1;
	}
	if(loadspr("res/tile.spr", tiles) < 0) {
		fprintf(stderr, "failed to load tileset file\n");
		deinit(stage);
		return -1;
	}
	if(loadspr("res/bg.spr", bg) < 0) {
		fprintf(stderr, "failed to load background file\n");
		free(tiles);
		deinit(stage);
		return -1;
	}

	srand(time(NULL));

	for(i = 0; i < stage->w*stage->h; i++)
		stage->pattern[i] = rand()%2;

	stage->x = platform_screenw/2 - (stage->w*tiles->h)/2;
	stage->y = platform_screenh/2 - (stage->h*tiles->h)/2;

	drawsprtiled(bg, 0, 0, platform_screenw, platform_screenh);
	hintdraw(stage, tiles);
	stagedraw(stage, tiles);
	showcursor();

	while(running) {
		platform_yield();
		tick(stage, tiles);
	}

	deinit(stage);
	return 0;
}
