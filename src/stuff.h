#define	nelem(x)	(sizeof(x)/sizeof((x)[0]))

enum {
	SPR_UNCHECKED,
	SPR_CHECKED,
	SPR_GUIDE,
	SPR_NUMBER = SPR_GUIDE,
	SPR_LAST = SPR_NUMBER + 12,
};

typedef struct {
	int x, y;
	int w, h;
	char *tiles;
	char *pattern;
} Stage;

typedef struct {
	int w, h;
	unsigned char *data;
} Sprite;

Stage *newstage(int w, int h);
void delstage(Stage *s);

int loadpal(char *);
int loadspr(char *, Sprite *);

void drawspr(int, int, Sprite *);
void drawsprtiled(Sprite *, int, int, int, int);
void drawtile(int, int, Sprite *, int);
