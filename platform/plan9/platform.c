#include <stdlib.h>

#define _PLAN9_SOURCE
#include <u.h>
#include <draw.h>
#include <event.h>

#include "../../platform.h"

static Image *pal[256];
static Mouse mouse;

int pcolors = 256;
int pscreenw;
int pscreenh;

void
sysfatal(char *s)
{
	print(s);
	exit(-1);
}

void
pinit(void)
{
	if(initdraw(0, 0, "asdf") < 0)
		sysfatal("initdraw: %r");

	pscreenw = Dx(screen->r);
	pscreenh = Dy(screen->r);
}

void
pyield(void)
{
	flushimage(display, 1);
	mouse = emouse();
}

void pdeinit(void) {}
void pshowcursor(void) {}
void phidecursor(void) {}
void pmousecallback(void (*f)(void)) {}

int
pmouseinit(void)
{
	einit(Emouse);
	return 0;
}

void
pmousestat(int *x, int *y, char *down)
{
	*x = mouse.xy.x - screen->r.min.x;
	*y = mouse.xy.y - screen->r.min.y;
	*down = mouse.buttons;
}

void
pdrawpixel(int x, int y, uchar color)
{
	draw(screen, Rect(screen->r.min.x + x, screen->r.min.y + y, screen->r.min.x + x + 1, screen->r.min.y + y + 1), pal[color], nil, ZP);
}

void
psetcolor(uchar i, ulong color)
{
	if(pal[i] && freeimage(pal[i]) < 0)
		sysfatal("freeimage: %r");
	pal[i] = allocimage(display, Rect(0, 0, 1, 1), RGB24, 1, color<<8 | 0xff);
	if(pal[i] == nil)
		sysfatal("allocimage: %r");
}

void
eresized(int new)
{
	if(new && getwindow(display, Refnone) < 0)
		sysfatal("getwindow: %r");

	pscreenw = Dx(screen->r);
	pscreenh = Dy(screen->r);

	presized();
}
