#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl

template<size_t n>
struct fact; // Inconplete declaration

template<>
struct fact<0> // base case
{
	constexpr static size_t value = 1;
};

template<size_t n>
struct fact // recursion
{
	constexpr static size_t value = n * fact<n - 1>::value;
};




int main()
{
	LOG(fact<5>::value);

}
