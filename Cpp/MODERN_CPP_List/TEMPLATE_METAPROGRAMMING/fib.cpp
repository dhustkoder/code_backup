#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl


template<size_t n>
struct fib;		// Declaration

template<>
struct fib<0> // Base case 0
{
	constexpr static size_t result = 1;
};
template<>
struct fib<1> // Base case 1
{
	constexpr static size_t result = 1;
};

template<size_t n>
struct fib // Recursion
{
	constexpr static size_t result = fib< n - 1>::result + fib<n - 2 >::result;
};


int main() {
	LOG(fib<5>::result);
}