extern const int platform_colors;

void platform_init(void);
void platform_deinit(void);
void drawpixel(int x, int y, unsigned char color);
void setcolor(unsigned char index, unsigned long color);
