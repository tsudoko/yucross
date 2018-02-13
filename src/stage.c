#include <stdlib.h>

#include "stage.h"

Stage *
newstage(int size)
{
	Stage *s = malloc(sizeof(Stage));
	s->tiles = calloc(size, 1);
	s->size  = size;

	if(s->tiles == NULL)
		return NULL;

	return s;
}

void
delstage(Stage *s)
{
	free(s->tiles);
	free(s);
}
