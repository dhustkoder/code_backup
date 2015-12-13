#include <time.h>
#include <stdlib.h>

typedef struct Timer
{
	struct timespec from;
}Timer;

void TIMER_start(struct Timer *tim)
{ 
	clock_gettime(CLOCK_MONOTONIC, &tim->from); 
}

double TIMER_elapsed(struct Timer *tim)
{
	struct timespec to;
	clock_gettime(CLOCK_MONOTONIC, &to);
	return to.tv_sec - tim->from.tv_sec + 1E-9 * (to.tv_nsec - tim->from.tv_nsec);
}

