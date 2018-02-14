#include <dos.h>

#include "../../platform.h"

/* only the NEC mouse driver is supported */

int
mouseinit(void)
{
	union REGS regs;
	regs.x.ax = 0;

	int86(0x33, &regs, &regs);
	if(!regs.x.ax)
		return -1;

	regs.x.ax = 1;
	int86(0x33, &regs, &regs);
	return 0;
}

void
mousedeinit(void)
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
		*down = (regs.x.bx << 1) | regs.x.ax;
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
