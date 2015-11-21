#include <iostream>
#include <functional>
#include <chrono>
#include <random>

#define LOG(x) std::cout << x << std::endl 

/* 
		In order to set a range for the random values.
		we better use distribution

		lets see with a random range between 0 and 5
*/
template<typename T>
void callNtimes(size_t callTimes, std::function<T> func) {
	for (; callTimes != 0; --callTimes)
		func();
}


void bad_quality() {
	size_t seed = std::chrono::steady_clock::now().time_since_epoch().count();

	std::default_random_engine engine(seed);

	callNtimes<void()>(10, [&engine]()
	{
		LOG(engine() % 6);  // call it 10 times.
	});

	// random number between 0 and 5
	// 1. bad quality of randomness
	// 2. can only provide uniform distribution

}


void uniform_distribution() {
	std::default_random_engine eng(std::chrono::steady_clock::now().time_since_epoch().count());

	std::uniform_int_distribution<int> distr(0, 5);

	callNtimes<void()>(10, [&eng, &distr]()
	{
		LOG(distr(eng));
	});
}
int main() 
{
	LOG("\n\n\t +-+-+-+ Not using distribution +-+-+-+ \n\n");
	bad_quality();
	LOG("\n\n\t +-+-+-+ Using distribution +-+-+-+ \n\n");
	uniform_distribution();

}