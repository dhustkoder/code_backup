#include <iostream>
// Template Meta-Programming C++ 
// Diving in....


// sizeof is a built-in type function, but we can write our own

// example: obtain the compile-time rank of an array type

template<class T>
struct rank
{
	static constexpr size_t value = 0u;
};


//partial specialization recognizes any array type
template<class U, size_t N>
struct rank<U[N]>
{
	static constexpr size_t value = 1u + rank<U>::value;
};


// this shows that the recursion doesn't need to go in the primary template, it can go in the specialization
// the template<class T> rank, is the base case now.

int main()
{
	//Usage
	using array_t = int[10][20][30];
	
	std::cout << rank<array_t>::value << std::endl;// 3
	

}