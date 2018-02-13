typedef struct {
	char *tiles;
	int   size;
} Stage;

Stage *newstage(int size);
void delstage(Stage *s);
