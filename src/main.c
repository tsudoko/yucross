#include <machine.h>

#include "platform.h"

#include "stuff.h"

int mx, my;
char mbut;

void
tick(void)
{

	mousestat(&mx, &my, &mbut);

	if(mbut)
		printf("mouse click (%d, %d)\n", mx, my);
}

int
main(void)
{
	Stage *s;
	Sprite *tiles;
	int colors;
	int i, j;
	platform_init();
	mouseinit();
	s = newstage(12*12);
	colors = loadpal("res\\pink.pal");
	loadspr("res\\tile.spr", tiles);

	drawspr(50, 30, tiles);
	for(i = 0; i < colors; i++) {
		for(j = i*4; j < i*4+4; j++) {
			drawpixel(j, j, i);
			drawpixel(j, j+1, i);
			drawpixel(j, j+2, i);
			drawpixel(j, j+3, i);
		}
	}

	for(i = 0; i < 12; i++) {
		for(j = 0; j < 12; j++) {
			drawtile(120+(i*tiles->h), 100+(j*tiles->h), tiles, 0);
		}
	}

	drawtile(120, 71, tiles, 2);
	drawtile(125, 71, tiles, 2);
	/*
	drawtile(127, 71, tiles, 2);
	drawtile(128, 71, tiles, 2);
	*/
	drawtile(301, 100, tiles, SPR_NUMBER + 6);
	drawtile(317, 100, tiles, SPR_NUMBER + 9);

	/* mousecallback(tick); */

	/* while(platform_event())? */
	for(;;) {
		tick();
	}

	delstage(s);
	/* platform_deinit(); */
	mousedeinit();
	return 0;
}
