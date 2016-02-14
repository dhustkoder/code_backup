#include <iostream>
// Template Meta-Programming C++ 
// Diving in....



// When Meta-programming, run-time == compile-time, so can't rely on:
// Mutability, Virtual functions, other RTTI, etc..
// put it simply... (NO RUN-TIME)



// Example how to shift work to compile-time

// lets make abs operation on compile time (if the value is known at compile time)


template<int N>
struct compile_time_abs
{
	static_assert(N != INT32_MIN,"");
	static constexpr int value = (N<0) ? -N : N;
};

// How do we use a META FUNCTION like the one above.

void use_meta_functions()
{
	static_assert(compile_time_abs<-10>::value == 10,"");
	std::cout << "passed!\n";
}


// a C++11 constexpr function can be useful
// the abs with constexpr function

constexpr int constexpr_abs(int N){
	return (N<0) ? -N : N;
}



void use_constexpr_function()
{

	static_assert(constexpr_abs(-10) == 10,"");
	std::cout << "passed!\n";
}


// But, as structs, metafunctions offer more tools, e.g:
// public member type declarations (e.g, typedef or using
// public member data declarations (static const/constexpr, each initialized via a constant expression)
// public member functions declarations and constexpr member function definition.
// public member templates, static_asserts, and more!

int main()
{
	use_meta_functions();
	use_constexpr_function();
	

}