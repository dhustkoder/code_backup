#include <time.h>
#include <stdlib.h>

typedef struct Timer
{
	clock_t from;
}Timer;

void TIMER_start(struct Timer *tim)
{ 
	tim->from = clock(); 
}

double TIMER_elapsed(struct Timer *tim)
{
	return (clock() - tim->from);
}