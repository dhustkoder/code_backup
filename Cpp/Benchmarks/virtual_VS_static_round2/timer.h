#include <time.h>

struct Timer
{
	Timer() {  }
	void start() { clock_gettime(CLOCK_MONOTONIC, &from); }
	struct timespec from;
	double elapsed() const
	{
		struct timespec to;
		clock_gettime(CLOCK_MONOTONIC, &to);
		return to.tv_sec - from.tv_sec + 1E-9 * (to.tv_nsec - from.tv_nsec);
	}
};