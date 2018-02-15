#include <stdlib.h>

#define _PLAN9_SOURCE
#include <u.h>
#include <draw.h>
#include <event.h>

static Image *pal[256];
static Mouse mouse;

int platform_colors = 256;
int platform_screenw;
int platform_screenh;

void
sysfatal(char *s)
{
	print(s);
	exit(-1);
}

void
platform_init(void)
{
	if(initdraw(0, 0, "asdf") < 0)
		sysfatal("initdraw: %r");

	platform_screenw = Dx(screen->r);
	platform_screenh = Dy(screen->r);
}

void
platform_yield(void) {
	flushimage(display, 1);
	mouse = emouse();
}

void platform_deinit(void) {}
void mousedeinit(void) {}
void mousecallback(void (*f)(void)) {}
int keypoll(void) { return 0; }

int
mouseinit(void)
{
	einit(Emouse);
	return 0;
}

void
mousestat(int *x, int *y, char *down)
{
	*x = mouse.xy.x - screen->r.min.x;
	*y = mouse.xy.y - screen->r.min.y;
	*down = mouse.buttons;
}

void
drawpixel(int x, int y, uchar color)
{
	draw(screen, Rect(screen->r.min.x + x, screen->r.min.y + y, screen->r.min.x + x + 1, screen->r.min.y + y + 1), pal[color], nil, ZP);
}

void
setcolor(uchar i, ulong color)
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

	platform_screenw = Dx(screen->r);
	platform_screenh = Dy(screen->r);
}
