#include <iostream>
#include <algorithm>
#include <vector>
#include <chrono>
#include <random>

#define LOG(x) std::cout << x << std::endl

template<typename T>
void printVec(std::vector<T> &v) {
	for (auto i : v)
		LOG(i);
}


void example() {

	// we can use random_engine to help us shuffle a vector

	std::vector<int> vec{ 10, 20, 30, 40, 50 };

	LOG("\n\n\tbefore shuffle...");
	printVec(vec);

	std::shuffle(vec.begin(), vec.end(), std::default_random_engine(std::chrono::steady_clock::now().time_since_epoch().count()));

	LOG("\n\n\tafter shuffle...");
	printVec(vec);

}




int main() {
	example();
}