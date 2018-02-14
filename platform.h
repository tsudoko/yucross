extern const int platform_colors;

void platform_init(void);
void platform_deinit(void);
void drawpixel(int x, int y, unsigned char color);
void setcolor(unsigned char index, unsigned long color);
int mouseinit(void);
void mousedeinit(void);
void mousestat(int *x, int *y, char *down);
void mousecallback(void (*f)(void));
