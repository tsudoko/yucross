#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum {
	SPR_UNCHECKED,
	SPR_CHECKED,
	SPR_GUIDE,
	SPR_NUMBER = SPR_GUIDE,
	SPR_LAST = SPR_NUMBER + 12,
};

typedef struct {
	char *tiles;
	int   size;
} Stage;

typedef struct {
	int w, h;
	unsigned char *data;
} Sprite;

Stage *newstage(int size);
void delstage(Stage *s);

int loadpal(char *);
int loadspr(char *, Sprite *);

void drawspr(int, int, Sprite *);
