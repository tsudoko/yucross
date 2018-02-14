#include "platform.h"
#include "stuff.h"

/* TODO: split into drawbg, drawtile */
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
drawtile(int sx, int sy, Sprite *tiles, int id)
{
	int tilepx = tiles->h;
	int x1 = tilepx*id;
	int x, y;

	for(y = 0; y < tilepx; y++) {
		for(x = 0; x < tilepx; x++) {
			drawpixel(sx+x, sy+y, tiles->data[y*tiles->w + x1 + x]);
		}
	}
}
