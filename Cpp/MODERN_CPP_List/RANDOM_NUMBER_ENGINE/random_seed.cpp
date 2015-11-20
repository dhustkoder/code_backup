#include <iostream>
#include <chrono>
#include <random>

#define LOG(x) std::cout << x << std::endl


/* random seed: 
	a "seed" is used to give the random engine some value to base their generated random numbers on.
	without it we will get repeated values.

	commonly a clock is used to seed.

*/

// print 4 random values:
void print_values(std::default_random_engine &eng) {
	for (int i = 0; i < 4; ++i)
		LOG(eng());
}


// without seed the engine
void without_seed()
{
	LOG("\n\n\t+-+-+-+-+-+-+-+ Without Seed +-+-+-+-+-+-+-+\n\n");
	std::default_random_engine eng_1;
	std::default_random_engine eng_2;
	
	LOG("printing eng_1...\n");
	print_values(eng_1);

	LOG("\n\nprinting eng_2...\n");
	print_values(eng_2);

	// we got the same values

}


void with_seed()
{
	LOG("\n\n\t+-+-+-+-+-+-+-+ With Seed +-+-+-+-+-+-+-+\n\n");

	std::default_random_engine eng_1(std::chrono::steady_clock::now().time_since_epoch().count());
	std::default_random_engine eng_2(std::chrono::steady_clock::now().time_since_epoch().count());
	
	LOG("printing eng_1...\n");
	print_values(eng_1);

	LOG("\n\nprinting eng_2...\n");
	print_values(eng_2);

	// we got different values


}

int main()
{
	without_seed();
	with_seed();
}