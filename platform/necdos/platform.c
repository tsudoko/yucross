#include <dos.h>

#include "../../platform.h"

void platform_yield(void) {}

/* only the NEC mouse driver is supported */

int
mouseinit(void)
{
	union REGS regs;
	regs.x.ax = 0;

	int86(0x33, &regs, &regs);
	if(!regs.x.ax)
		return -1;

	return 0;
}

void
showcursor(void)
{
	union REGS regs;
	regs.x.ax = 1;
	int86(0x33, &regs, &regs);
}

void
hidecursor(void)
{
	union REGS regs;
	regs.x.ax = 2;
	int86(0x33, &regs, &regs);
}

void
mousestat(int *x, int *y, char *down)
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

void
mousecallback(void (*func)(void))
{

	union REGS regs;
	void (far *farfunc)(void);

	farfunc = func;
	regs.x.ax = 0x0c;
	/*regs.x.cx = 1<<1; /* left button press */
	regs.x.cx = 0;

	regs.x.es = FP_OFF(farfunc);
	regs.x.dx = FP_SEG(farfunc);
}

int
keypoll(void)
{
	union REGS regs;
	regs.h.ah = 0;
	int86(0x18, &regs, &regs);
	return regs.h.ah;
}
