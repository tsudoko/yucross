extern const int platform_colors;
extern const int platform_screenw;
extern const int platform_screenh;

void platform_init(void);
void platform_deinit(void);
void platform_yield(void);
void drawpixel(int x, int y, unsigned char color);
void setcolor(unsigned char index, unsigned long color);
int mouseinit(void);
void mousedeinit(void);
void mousestat(int *x, int *y, char *down);
void mousecallback(void (*f)(void));
