#include <stdlib.h>
#include <stdio.h>
#include <string.h>

enum {
	SPR_UNCHECKED,
	SPR_CHECKED,
	SPR_GUIDE,
	SPR_NUMBER = SPR_GUIDE,
	SPR_LAST = SPR_NUMBER + 12,
};

typedef struct {
	int w, h;
	unsigned char *data;
} Sprite;

int loadpal(char *);
int loadspr(char *, Sprite *);

void drawspr(int, int, Sprite *);
