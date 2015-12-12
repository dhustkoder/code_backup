#include <time.h>
#include <stdlib.h>

struct Timer
{
	Timer() {  }
	inline void start() const noexcept { from = clock(); }
	mutable clock_t from;
	inline double elapsed() const noexcept
	{
		auto to = clock();
		return to - from;
	}
};