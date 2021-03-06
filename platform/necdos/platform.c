#include <dos.h>

#include "../../platform.h"

void pyield(void) {}

/* only the NEC mouse driver is supported */

int
pmouseinit(void)
{
	union REGS regs;
	regs.x.ax = 0;

	int86(0x33, &regs, &regs);
	if(!regs.x.ax)
		return -1;

	return 0;
}

void
pshowcursor(void)
{
	union REGS regs;
	regs.x.ax = 1;
	int86(0x33, &regs, &regs);
}

void
phidecursor(void)
{
	union REGS regs;
	regs.x.ax = 2;
	int86(0x33, &regs, &regs);
}

void
pmousestat(int *x, int *y, char *down)
{
	union REGS regs;
	regs.x.ax = 3;
	int86(0x33, &regs, &regs);

	if(x)
		*x = regs.x.cx;

	if(y)
		*y = regs.x.dx;

	if(down)
		*down = ((regs.x.bx & 1) << 2) | regs.x.ax & 1;
}
