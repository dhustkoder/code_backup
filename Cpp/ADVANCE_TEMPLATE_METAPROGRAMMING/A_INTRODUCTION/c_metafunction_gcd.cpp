#include <iostream>
// Template Meta-Programming C++ 
// Diving in....

// Compile-time recursion with specialization


// Example: primary template for gcd(m,n)
// (compile-time greatest common divisior calculation
template<unsigned M, unsigned N>
struct gcd
{
	static constexpr int value = gcd<N,M%N>::value;
};


// As this is a recursion we need  a BASE CASE

// Much like pattern matching, this partial specialization
// recognize the base case of ( gcd(m,0) ):

template<unsigned M>
struct gcd<M,0>
{
	static_assert(M!= 0, ""); // gcd(0,0) is undefined so disallow
	static constexpr int value = M;
};


int main()
{
	std::cout << gcd<64,32>::value << std::endl;

}