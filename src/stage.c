#include "stuff.h"

Stage *
newstage(int w, int h)
{
	Stage *s = malloc(sizeof(Stage));
	s->tiles = calloc(w*h, 1);
	s->pattern = calloc(w*h, 1);
	s->w = w;
	s->h = h;

	if(s->tiles == NULL)
		return NULL;

	return s;
}

void
delstage(Stage *s)
{
	free(s->tiles);
	free(s->pattern);
	free(s);
}
