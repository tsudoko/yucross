extern const int pcolors;
extern const int pscreenw;
extern const int pscreenh;

void pinit(void);
void pdeinit(void);
void pyield(void);
void pdrawpixel(int x, int y, unsigned char color);
void psetcolor(unsigned char index, unsigned long color);
int  pmouseinit(void);
void pshowcursor(void);
void phidecursor(void);
void pmousestat(int *x, int *y, char *down);

/* provided by the application */
void presized(void);
