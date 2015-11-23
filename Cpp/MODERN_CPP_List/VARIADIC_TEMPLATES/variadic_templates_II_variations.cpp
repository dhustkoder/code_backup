#include <iostream>
#include <string>
#define LOG(x) std::cout << x << std::endl

/* Some Simple Variations

	When reading about C++ template meta-programming, one often hears about "pattern matching" and how this part
	of the language consistitues a fairly complete compile-time functional language

	The example showed before is very basic - template arguments are peeled off one by one until the base case is hit

	Here's a somewhat more interesting display of pattern matching:

*/


template<typename T>
bool pair_comparer(T single) {
	return false;
}

template<typename T>
bool pair_comparer(T a, T b) {
	return a == b;
}


template<typename T, typename ...Args>
bool pair_comparer(T a, T b, Args ...args) {
	return a == b && pair_comparer(args...);
}


int main(void) 
{
	if (pair_comparer(2, 2, 4, 4, 6, 6))
		LOG("equal pairs");

	if (!pair_comparer(3, 3, 4, 3))
		LOG("not equal pairs");

	/* 
	
		pair_comparer, accepts any number of arguments (even numbers) and returns true if
		and only if they are pair-wise equal. Everything that have the overloaded operator == can be used.

		pair_comparer(1.2, 1.2) compiles but
		pair_comparer(1.2, 1) does not: because float and int are not the same type.


		as said pair_comparer will only work for an even number of arguments because they are peeled off in pairs
		and the base case compares 2:
		pair_comparer(1,1,2) does not compile

		the compiler compains that the base case expects 2 arguments but only 1 is provided.

		we can add another base case that accepts 1 parameter
			bool pair_comparer(T single) {
				return false;
			}

		Here, we force all odd-numbered sequences of arguments to return false,
		because when only a single argument is left this version is matched.


		Performance:
			If you're concerned with the performance of code that relies on variadic templates, worry not. 
			As there's no actual recursion involved, all we have is a sequence of function calls pre-generated at compile-time. 
			This sequence is, in practice, fairly short (variadic calls with more than 5-6 arguments are rare). 
			Since modern compilers are aggressively inlining code, it's likely to end up being compiled to machine code that has absolutely no 
			function calls. What you end up with, actually, is not unlike loop unrolling.

			Compared to the C-style variadic functions, 
			this is a marked win, because C-style variadic arguments have to be resolved at runtime. 
			The va_ macros are literally manipulating the runtime stack. Therefore, variadic 
			templates are often a performance optimization for variadic functions.


	*/

}