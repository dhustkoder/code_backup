#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <random>

#define LOG(x) std::cout << x << std::endl







void distribution_types()
{
	std::default_random_engine eng((unsigned)std::chrono::steady_clock::now().time_since_epoch().count());


	std::uniform_int_distribution<int> uniform_distr(0, 10); // range [ 0, 10 ]
	LOG(uniform_distr(eng));


	std::uniform_real_distribution<double> uniform_real_distr(4, 8); // range [ 4, 8]
	LOG(uniform_real_distr(eng));


	std::poisson_distribution<int> poisson_distr(1.0); // mean
	LOG(poisson_distr(eng));



	LOG("normal distribution mean and deviation example: ");

	std::normal_distribution<double> normal_distr(10, 20); // mean and standard deviation.
	// the lower the deviation, more often we will get number 10 generated and vice versa.

	// print the values generated in range of [ 0, 19 ] represented by *
	std::vector<int> vec(20);
	for (int i = 0; i < 800; ++i){
		int generatedNumber = (int)normal_distr(eng);
		if (generatedNumber >= 0 && generatedNumber < 20)
			vec[generatedNumber]++;
	}
	for (int i = 0; i < 20; ++i) {
		LOG(i << ": " << std::string(vec[i], '*'));
	}




}

int main()
{
	distribution_types();
}