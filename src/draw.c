#include "../platform.h"
#include "stuff.h"

void
drawspr(int sx, int sy, Sprite *s)
{
	int x, y;

	for(y = 0; y < s->h; y++) {
		for(x = 0; x < s->w; x++) {
			if(!s->data[y*s->w + x])
				continue;

			drawpixel(sx+x, sy+y, s->data[y*s->w + x]);
		}
	}
}

void
drawsprtiled(Sprite *s, int x1, int y1, int x2, int y2)
{
	int x, y;

	hidecursor(); /* hack to prevent pointer burn-in on necdos */
	for(y = y1; y < y2; y++) {
		for(x = x1; x < x2; x++) {
			if(!s->data[(y%s->h)*s->w + (x%s->w)])
				continue;

			drawpixel(x, y, s->data[(y%s->h)*s->w + (x%s->w)]);
		}
	}
	showcursor();
}

void
drawtile(int sx, int sy, Sprite *tiles, int id)
{
	int tilepx = tiles->h;
	int x1 = tilepx*id;
	int x, y;

	hidecursor(); /* hack to prevent pointer burn-in on necdos */
	for(y = 0; y < tilepx; y++) {
		for(x = 0; x < tilepx; x++) {
			if(!tiles->data[y*tiles->w + x1 + x])
				continue;

			drawpixel(sx+x, sy+y, tiles->data[y*tiles->w + x1 + x]);
		}
	}
	showcursor();
}
